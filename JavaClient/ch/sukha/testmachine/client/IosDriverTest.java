package ch.sukha.testmachine.client;

import junit.framework.*;

public class IosDriverTest extends TestCase {

    private final static String _deviceIp = "192.168.1.69";
    
    private IosDriver _driver;
    
    public void setUp() throws Exception {
        _driver = new IosDriver(_deviceIp);
        _driver.setPort(59247);  // Settings app
    }
    
	public void testTap() throws Exception {
	    _driver.tap("//PSTableCell[title[contains(text(), 'About')]]");
	} 
	
	public void testTapXY() throws Exception {
        _driver.tap("//PSTableCell[title[contains(text(), 'About')]]", 10, 10);
	} 

    public void testSwipe() throws Exception {
        _driver.swipe("//UIWindow", 0, 200, 0, 0);
    }

    public void testSetText() throws Exception {
        _driver.setText("//UITextField", "Peter Farkas's iPad");
    }
    
    public void testSetSwitch() throws Exception {
        _driver.setSwitch("//PSControlTableCell[text[contains(text(), 'Ask to Join Networks')]]//UISwitch", true);
    }
    
    public void testCheck() throws Exception {
        _driver.setTimeout(5.0);
        
        assertFalse(_driver.check("//PSTableCell[title[contains(text(), 'Bouta')]]"));
        
        assertTrue(_driver.check("//PSTableCell[title[contains(text(), 'About')]]"));
    }
    
    public void testPlayingSound() throws Exception {
        _driver.startPlayingSound("resources/thermo.wav");
        
        Thread.sleep(1000);
        
        _driver.pausePlayingSound();
        
        Thread.sleep(1000);
        
        _driver.resumePlayingSound();
    }
    
    public void testRecordingSound() throws Exception {
        _driver.startRecordingSound(22050);
        
        Thread.sleep(5000);

        _driver.finishRecordingSound("bin/recroding.wav");
    }
    
    public void testOpenUrl() throws Exception {
        _driver.setPort(50000);
        _driver.openUrl("prefs://");
    }

    public void testNotifyPost() throws Exception {
        _driver.notifyPost("reboot", 2);
    }
    
}