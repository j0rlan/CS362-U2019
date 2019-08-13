package test;
import static org.junit.Assert.*;

import java.util.regex.Matcher;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import files.UrlValidator;

//import files.UrlValidator;//wouldn't work unless I added this, you might have to change it depending on how your eclipse project is set up
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;


public class UnitTest {
	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}
    
	
	@Test
	public void testIsValid() {
		//test with default schemes ("http", "https", "ftp")
		UrlValidator urlVal = new UrlValidator();
		
		BufferedReader reader;
		
		//change fileNombre to the exact location of test.txt
		String fileNombre = "/home/artemis/kamillamagna/362GroupProject/CS362-U2019/FinalProject/URLValidatorInCorrect/test/test.txt";
//		String fileNombre = "C:\\\\Users\\\\scott\\\\eclipse-workspace\\\\CS362-U2019\\\\projects\\\\bleckw\\\\FinalProject\\\\URLValidatorInCorrect\\\\Final\\\\src\\\\test\\\\test.txt";
		try {
			reader = new BufferedReader(new FileReader(fileNombre));
			String line = reader.readLine();
			while (line != null) {
				System.out.println(line);
				
				//Test null returns false
				if(line.equals("null")) {
					
					assertFalse(urlVal.isValid(null));
				}
				
				//Test that default schemes return true
				else {
				
					if(line.charAt(0) == 'h' && line.charAt(1) =='t' && line.charAt(2) =='t' && line.charAt(3) =='p' && line.charAt(4) == 's') {
						assertTrue(urlVal.isValid(line));
					}
					
					else if(line.charAt(0) == 'h' && line.charAt(1) =='t' && line.charAt(2) =='t' && line.charAt(3) =='p') {
						assertTrue(urlVal.isValid(line));
					}
					
					else if(line.charAt(0) == 'f' && line.charAt(1) =='t' && line.charAt(2) =='p') {
						assertTrue(urlVal.isValid(line));
					}
					
				}
				
				//if()
				
				// read next line
				line = reader.readLine();
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		
	}

}
