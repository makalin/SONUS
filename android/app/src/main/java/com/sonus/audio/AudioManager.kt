package com.sonus.audio

import android.content.Context
import android.media.AudioFormat
import android.media.AudioRecord
import android.media.MediaRecorder
import android.media.AudioTrack
import android.media.AudioManager as AndroidAudioManager
import com.sonus.SonusApp
import com.sonus.core.SonusCore
import java.nio.ByteBuffer
import java.nio.ByteOrder

class AudioManager(private val context: Context) {
    private val core = SonusCore()
    private var audioRecord: AudioRecord? = null
    private var audioTrack: AudioTrack? = null
    private var isRecording = false
    private var isPlaying = false

    companion object {
        private const val SAMPLE_RATE = 44100
        private const val CHANNEL_CONFIG = AudioFormat.CHANNEL_IN_MONO
        private const val AUDIO_FORMAT = AudioFormat.ENCODING_PCM_FLOAT
        private const val BUFFER_SIZE = 4096
    }

    fun startRecording(onDataReceived: (ByteArray) -> Unit) {
        if (isRecording) return

        val minBufferSize = AudioRecord.getMinBufferSize(
            SAMPLE_RATE,
            CHANNEL_CONFIG,
            AUDIO_FORMAT
        )

        audioRecord = AudioRecord(
            MediaRecorder.AudioSource.MIC,
            SAMPLE_RATE,
            CHANNEL_CONFIG,
            AUDIO_FORMAT,
            minBufferSize
        )

        audioRecord?.startRecording()
        isRecording = true

        Thread {
            val buffer = ByteArray(BUFFER_SIZE)
            while (isRecording) {
                val read = audioRecord?.read(buffer, 0, buffer.size) ?: 0
                if (read > 0) {
                    onDataReceived(buffer.copyOf(read))
                }
            }
        }.start()
    }

    fun stopRecording() {
        isRecording = false
        audioRecord?.stop()
        audioRecord?.release()
        audioRecord = null
    }

    fun playAudio(data: ByteArray) {
        if (isPlaying) return

        val minBufferSize = AudioTrack.getMinBufferSize(
            SAMPLE_RATE,
            AudioFormat.CHANNEL_OUT_MONO,
            AUDIO_FORMAT
        )

        audioTrack = AudioTrack(
            AndroidAudioManager.STREAM_MUSIC,
            SAMPLE_RATE,
            AudioFormat.CHANNEL_OUT_MONO,
            AUDIO_FORMAT,
            minBufferSize,
            AudioTrack.MODE_STREAM
        )

        audioTrack?.play()
        isPlaying = true

        Thread {
            audioTrack?.write(data, 0, data.size)
            stopPlaying()
        }.start()
    }

    fun stopPlaying() {
        isPlaying = false
        audioTrack?.stop()
        audioTrack?.release()
        audioTrack = null
    }

    fun encodeSOS(): ByteArray {
        val sosSignal = core.encodeSOS()
        return floatArrayToByteArray(sosSignal)
    }

    fun encodeGPS(latitude: Double, longitude: Double): ByteArray {
        val gpsSignal = core.encodeGPS(latitude, longitude)
        return floatArrayToByteArray(gpsSignal)
    }

    private fun floatArrayToByteArray(floatArray: FloatArray): ByteArray {
        val byteBuffer = ByteBuffer.allocate(floatArray.size * 4)
        byteBuffer.order(ByteOrder.LITTLE_ENDIAN)
        floatArray.forEach { byteBuffer.putFloat(it) }
        return byteBuffer.array()
    }

    private fun byteArrayToFloatArray(byteArray: ByteArray): FloatArray {
        val floatBuffer = ByteBuffer.wrap(byteArray)
            .order(ByteOrder.LITTLE_ENDIAN)
            .asFloatBuffer()
        val floatArray = FloatArray(floatBuffer.remaining())
        floatBuffer.get(floatArray)
        return floatArray
    }
} 