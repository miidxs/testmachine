package ch.sukha.testmachine.client;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Vector;

import org.apache.xmlrpc.XmlRpcClient;

public class IosDriver {

    private final int DEFAULT_PORT = 50000;
    
    private final double TIME_GAP = 2.0;
    
    private String _deviceIp;
    
    private double _timeOut = 60.0;

    private XmlRpcClient _client;
    
    private double _startTime;

    public IosDriver(String deviceIp) throws Exception {
        _deviceIp = deviceIp;
        setPort(DEFAULT_PORT);
    }
    
    /**
     * Sets the port. Every app runs its own server on its own port.
     */
    public void setPort(int port) throws Exception {
        _client = new XmlRpcClient("http://" + _deviceIp + ":" + port + "/rpc");
    }
    
    /**
     * Sets the amount of the time, operations on UI elements should wait for the element to appear.
     */
    public void setTimeout(double timeOut) throws Exception {
        _timeOut = timeOut;
    }
    
    /**
     * Taps the element specified by the XPath expression at its center.
     * 
     * @throws Exception
     *              Thrown when the element didn't appear within timeout or the operation failed
     */
    public void tap(String xpath) throws Exception {
        reset();
        while (!((Boolean) execute("tap", xpath))) {
            failOrWait();
        }
    }

    /**
     * Taps the element specified by the XPath expression at the specified coordinates.
     * 
     * @throws Exception
     *              Thrown when the element didn't appear within timeout or the operation failed
     */
    public void tap(String xpath, double x, double y) throws Exception {
        reset();
        while (!((Boolean) execute("tap", xpath, x, y))) {
            failOrWait();
        }
    }
    
    /**
     * Performs a swipe on the element specified by the XPath expression.
     * 
     * @throws Exception
     *              Thrown when the element didn't appear within timeout or the operation failed
     */
    public void swipe(String xpath, double x1, double y1, double x2, double y2) throws Exception {
        reset();
        while (!((Boolean) execute("swipe", xpath, x1, y1, x2, y2))) {
            failOrWait();
        }
    }
    
    /**
     * Sets the text value of the element specified by the XPath expression.
     * 
     * @throws Exception
     *              Thrown when the element didn't appear within timeout or the operation failed
     */
    public void setText(String xpath, String text) throws Exception {
        reset();
        while (!((Boolean) execute("setText", xpath, text))) {
            failOrWait();
        }
    }
    
    /**
     * Sets the switch specified by the XPath expression on or off.
     * 
     * @throws Exception
     *              Thrown when the element didn't appear within timeout or the operation failed
     */
    public void setSwitch(String xpath, boolean on) throws Exception {
        reset();
        while (!((Boolean) execute("setSwitch", xpath, on))) {
            failOrWait();
        }
    }
    
    /**
     * Sets a component of the picker view specified by the XPath expression.
     * 
     * @throws Exception
     *              Thrown when the element didn't appear within timeout or the operation failed
     */
    public void selectPickerViewRow(String xpath, int rowIndex, int componentIndex) throws Exception {
        reset();
        while (!((Boolean) execute("selectPickerViewRow", xpath, rowIndex, componentIndex))) {
            failOrWait();
        }
    }

    /**
     * Scrolls a section of the table view specified by the XPath expression to a row.
     * 
     * @throws Exception
     *              Thrown when the element didn't appear within timeout or the operation failed
     */
    public void scrollToTableViewRow(String xpath, int sectionIndex, int rowIndex) throws Exception {
        reset();
        while (!((Boolean) execute("scrollToTableViewRow", xpath, sectionIndex, rowIndex))) {
            failOrWait();
        }
    }
    
    /**
     * Checks if the element specified by the XPath expression is present.
     * Returns false, if the element was not present, true if it was present.
     */
    public boolean check(String xpath) throws Exception {
        reset();
        while (!((Boolean) execute("check", xpath))) {
            long now = System.currentTimeMillis();
            if (now - _startTime > ((long) _timeOut * 1000.0)) {
                return false;
            }
            Thread.sleep((long) (TIME_GAP * 1000.0));
        }
        return true;
    }
    
    /**
     * Starts playing sound.
     */
    public void startPlayingSound(String soundFilePath) throws Exception {
        File f = new File(soundFilePath);
        byte[] data = new byte[(int) f.length()];
        FileInputStream s = new FileInputStream(f);
        s.read(data);
        s.close();
        
        execute("startPlayingSound", data);
    }
    
    /**
     * Pauses playing the sound.
     */
    public void pausePlayingSound() throws Exception {
        execute("pausePlayingSound");
    }
    
    /**
     * Resumes playing the sound.
     */
    public void resumePlayingSound() throws Exception {
        execute("resumePlayingSound");
    }
    
    /**
     * Starts recording sound in WAV file.
     */
    public void startRecordingSound(double sampleRate) throws Exception {
        execute("startRecordingSound", sampleRate);
    }
    
    /**
     * Finishes recording sound.
     * Return the sound as a raw byte array.
     */
    public void finishRecordingSound(String soundFilePath) throws Exception {
        byte[] data = (byte[]) execute("finishRecordingSound");

        FileOutputStream s = new FileOutputStream(soundFilePath);
        s.write(data);
        s.close();
    }
    
    /**
     * Opens another application and jumps to the specified module by calling UIApplication:openURL:.
     * The exact URL format is not documented, but examples can be found in the internet.
     */
    public void openUrl(String url) throws Exception {
        execute("openUrl", url);
    }
    
    /**
     * Calls an SBSettings command after a specified delay.
     * The purpose of the delay is to allow the call to return when invoking the reboot command.
     * The command must be installed on the phone. See http://stackoverflow.com/questions/6419678/iphone-reboot-programmatically.
     */
    public void notifyPost(String name, double delay) throws Exception {
        execute("notifyPost", name, delay);
    }
    
    private Object execute(String method, Object... args) throws Exception {
        Vector<Object> params = new Vector<Object>();
        for (Object arg : args) {
            params.add(arg);
        }
        return _client.execute(method, params);     
    }

    private void reset() {
        _startTime = System.currentTimeMillis();        
    }
    
    private void failOrWait() throws Exception {
        long now = System.currentTimeMillis();
        if (now - _startTime > ((long) _timeOut * 1000.0)) {
            throw new Exception("element not found");
        }
        Thread.sleep((long) (TIME_GAP * 1000.0));
    }
}
