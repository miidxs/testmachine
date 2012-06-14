using System;
using System.Text;
using System.Net;
using System.IO;
using System.Threading;
using CookComputing.XmlRpc;

/// <summary>
/// Interface to the test driver for the tests.
/// This class depends on XML-RPC.NET.
/// Download XML-RPC.NET http://xmlrpcnet.googlecode.com/files/xml-rpc.net.2.5.0.zip and add CookComputing.XmlRpcV2.dll to the project.
/// </summary> 
public class IosDriver {

    private const int DEFAULT_PORT = 50000;

    private const double TIME_GAP = 2.0;

    private String _deviceIp;

    private double _timeOut = 60.0;

    private IIosDriver _client;

    private DateTime _startTime;

    public IosDriver(String deviceIp) {
        _deviceIp = deviceIp;
        _client = XmlRpcProxyGen.Create<IIosDriver>();
        SetPort(DEFAULT_PORT);
    }

    /// <summary>
    /// Sets the port. Every app runs its own server on its own port. 
    /// </summary> 
    public void SetPort(int port) {
        _client.Url = "http://" + _deviceIp + ":" + port + "/rpc";
    }

    /// <summary>
    /// Sets the amount of the time, operations on UI elements should wait for the element to appear.
    /// </summary> 
    public void SetTimeOut(double timeOut) {
        _timeOut = timeOut;
    }

    /// <summary>
    /// Taps the element specified by the XPath expression at its center.
    /// <exception cref="System.Exception">Thrown when the element didn't appear within timeout or the operation failed</exception>
    /// </summary> 
    public void Tap(String xpath) {
        Reset();
        while (!_client.tap(xpath)) {
            FailOrWait();
        }
    }

    /// <summary>
    /// Taps the element specified by the XPath expression at the specified coordinates.
    /// <exception cref="System.Exception">Thrown when the element didn't appear within timeout or the operation failed</exception>
    /// </summary> 
    public void Tap(String xpath, double x, double y) {
        Reset();
        while (!_client.tap(xpath, x, y)) {
            FailOrWait();
        }
    }

    /// <summary>
    /// Performs a swipe on the element specified by the XPath expression, if the element is present.
    /// <exception cref="System.Exception">Thrown when the element didn't appear within timeout or the operation failed</exception>
    /// </summary> 
    public void Swipe(String xpath, double x1, double y1, double x2, double y2) {
        Reset();
        while (!_client.swipe(xpath, x1, y1, x2, y2)) {
            FailOrWait();
        }
    }

    /// <summary>
    /// Sets the text value of the element specified by the XPath expression.
    /// <exception cref="System.Exception">Thrown when the element didn't appear within timeout or the operation failed</exception>
    /// </summary> 
    public void SetText(String xpath, String text) {
        Reset();
        while (!_client.setText(xpath, text)) {
            FailOrWait();
        }
    }

    /// <summary>
    /// Sets the switch specified by the XPath expression on or off, if the element is present.
    /// <exception cref="System.Exception">Thrown when the element didn't appear within timeout or the operation failed</exception>
    /// </summary> 
    public void SetSwitch(String xpath, bool on) {
        Reset();
        while (!_client.setSwitch(xpath, on)) {
            FailOrWait();
        }
    }

    /// <summary>
    /// Sets a component of the picker view specified by the XPath expression, if the element is present.
    /// <exception cref="System.Exception">Thrown when the element didn't appear within timeout or the operation failed</exception>
    /// </summary> 
    public void SelectPickerViewRow(String xpath, int rowIndex, int componentIndex) {
        Reset();
        while (!_client.selectPickerViewRow(xpath, rowIndex, componentIndex)) {
            FailOrWait();
        }
    }

    /// <summary>
    /// Sets a component of the picker view specified by the XPath expression, if the element is present.
    /// <exception cref="System.Exception">Thrown when the element didn't appear within timeout or the operation failed</exception>
    /// </summary> 
    public void ScrollToTableViewRow(String xpath, int sectionIndex, int rowIndex) {
        Reset();
        while (!_client.scrollToTableViewRow(xpath, sectionIndex, rowIndex)) {
            FailOrWait();
        }
    }

    /// <summary>
    /// Checks if the element specified by the XPath expression is present.
    /// Returns false, if the element was not present, true if it was present.
    /// </summary>
    public bool Check(String xpath) {
        Reset();
        DateTime now = DateTime.Now;
        while (!_client.check(xpath)) {
            if (now.Subtract(_startTime).Seconds > _timeOut) {
                return false;
            }
            Thread.Sleep((int)(TIME_GAP * 1000.0));
        }
        return true;
    }

    /// <summary>
    /// Starts playing sound.
    /// </summary>
    public void StartPlayingSound(String soundFilePath) {
        FileStream s = new FileStream(soundFilePath, FileMode.Open);
        BinaryReader r = new BinaryReader(s);
        byte[] data = r.ReadBytes((int) s.Length);
        _client.startPlayingSound(data);
    }

    /// <summary>
    /// Pauses playing the sound.
    /// </summary>
    public void PausePlayingSound() {
        _client.pausePlayingSound();
    }

    /// <summary>
    /// Resumes playing the sound.
    /// </summary>
    public void ResumePlayingSound() {
        _client.resumePlayingSound();
    }

    /// <summary>
    /// Starts recording sound in WAV file.
    /// </summary>
    public void StartRecordingSound(double sampleRate) {
        _client.startRecordingSound(sampleRate);
    }

    /// <summary>
    /// Finishes recording sound.
    /// Return the sound as a raw byte array.
    /// </summary>
    public void FinishRecordingSound(String soundFilePath) {
        byte[] data = _client.finishRecordingSound();
        FileStream s = new FileStream(soundFilePath, FileMode.Create);
        s.Write(data, 0, data.Length);
        s.Close();
    }

    /// <summary>
    /// Opens another application and jumps to the specified module by calling UIApplication:openURL:.
    /// The exact URL format is not documented, but examples can be found in the internet.
    /// </summary>
    public void OpenUrl(String url) {
        _client.openUrl(url);
    }

    /// <summary>
    /// Calls an SBSettings command after a specified delay.
    /// The purpose of the delay is to allow the call to return when invoking the reboot command.
    /// The command must be installed on the phone. See http://stackoverflow.com/questions/6419678/iphone-reboot-programmatically.
    /// </summary>
    public void NotifyPost(String name, double delay) {
        _client.notifyPost(name, delay);
    }

    public interface IIosDriver : IXmlRpcProxy {

        [XmlRpcMethod("tap")]
        bool tap(String xpath);

        [XmlRpcMethod("tap")]
        bool tap(String xpath, double x, double y);

        [XmlRpcMethod("swipe")]
        bool swipe(String xpath, double x1, double y1, double x2, double y2);

        [XmlRpcMethod("setText")]
        bool setText(String xpath, String text);

        [XmlRpcMethod("setSwitch")]
        bool setSwitch(String xpath, bool on);

        [XmlRpcMethod("selectPickerViewRow")]
        bool selectPickerViewRow(String xpath, int rowIndex, int componentIndex);

        [XmlRpcMethod("scrollToTableViewRow")]
        bool scrollToTableViewRow(String xpath, int sectionIndex, int rowIndex);

        [XmlRpcMethod("check")]
        bool check(String xpath);

        [XmlRpcMethod("startPlayingSound")]
        void startPlayingSound(byte[] data);

        [XmlRpcMethod("pausePlayingSound")]
        void pausePlayingSound();

        [XmlRpcMethod("resumePlayingSound")]
        void resumePlayingSound();

        [XmlRpcMethod("startRecordingSound")]
        void startRecordingSound(double sampleRate);

        [XmlRpcMethod("finishRecordingSound")]
        byte[] finishRecordingSound();

        [XmlRpcMethod("openUrl")]
        void openUrl(String url);

        [XmlRpcMethod("notifyPost")]
        void notifyPost(String name, double delay);
    }

    private void Reset() {
        _startTime = DateTime.Now;
    }

    private void FailOrWait() {
        DateTime now = DateTime.Now;
        if (now.Subtract(_startTime).Seconds > _timeOut) {
            throw new Exception("element not found");
        }
        Thread.Sleep((int) (TIME_GAP * 1000.0));
    }
}