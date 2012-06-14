using System;
using System.Text;
using System.Net;
using System.IO;
using System.Threading;
using CookComputing.XmlRpc;

public class IPhoneDriver {

    public interface IXpathDriver : IXmlRpcProxy {

        [XmlRpcMethod("tap")]
        bool tap(String xpath);

        [XmlRpcMethod("tap")]
        bool tap(String xpath, double x, double y);

        [XmlRpcMethod("swipe")]
        bool swipe(String xpath, double x1, double y1, double x2, double y2);

        [XmlRpcMethod("setText")]
        bool setText(String xpath, String text);

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

    private const int DEFAULT_PORT = 50000;

    private const double TIME_GAP = 2.0;

    private String _deviceIp;

    private double _timeOut = 10.0;

    private IXpathDriver _client;

    private DateTime _startTime;

   public IPhoneDriver(String deviceIp) {
        _deviceIp = deviceIp;
        _client = XmlRpcProxyGen.Create<IXpathDriver>();
        SetPort(DEFAULT_PORT);
	}

    public void SetPort(int port) {
        _client.Url = "http://" + _deviceIp + ":" + port + "/rpc";
    }

    public void SetTimeOut(double timeOut) {
        _timeOut = timeOut;
    }

    public void Tap(String xpath) {
        Reset();
        while (!_client.tap(xpath)) {
            FailOrWait();
        }
    }

    public void Tap(String xpath, double x, double y) {
        Reset();
        while (!_client.tap(xpath, x, y)) {
            FailOrWait();
        }
    }

    public void Swipe(String xpath, double x1, double y1, double x2, double y2) {
        Reset();
        while (!_client.swipe(xpath, x1, y1, x2, y2)) {
            FailOrWait();
        }
    }

    public void SetText(String xpath, String text) {
        Reset();
        while (!_client.setText(xpath, text)) {
            FailOrWait();
        }
    }

    public void SelectPickerViewRow(String xpath, int rowIndex, int componentIndex) {
        Reset();
        while (!_client.selectPickerViewRow(xpath, rowIndex, componentIndex)) {
            FailOrWait();
        }
    }

    public void ScrollToTableViewRow(String xpath, int sectionIndex, int rowIndex) {
        Reset();
        while (!_client.scrollToTableViewRow(xpath, sectionIndex, rowIndex)) {
            FailOrWait();
        }
    }

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

    public void StartPlayingSound(String soundFilePath) {
        FileStream s = new FileStream(soundFilePath, FileMode.Open);
        BinaryReader r = new BinaryReader(s);
        byte[] data = r.ReadBytes((int) s.Length);
        _client.startPlayingSound(data);
    }

    public void PausePlayingSound() {
        _client.pausePlayingSound();
    }

    public void ResumePlayingSound() {
        _client.resumePlayingSound();
    }

    public void StartRecordingSound(double sampleRate) {
        _client.startRecordingSound(sampleRate);
    }

    public void FinishRecordingSound(String soundFilePath) {
        byte[] data = _client.finishRecordingSound();
        FileStream s = new FileStream(soundFilePath, FileMode.Create);
        s.Write(data, 0, data.Length);
        s.Close();
    }

    public void OpenUrl(String url) {
        _client.openUrl(url);
    }

    public void NotifyPost(String name, double delay) {
        _client.notifyPost(name, delay);
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
