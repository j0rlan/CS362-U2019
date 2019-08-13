package test;
import static org.junit.Assert.*;
import junit.framework.TestCase;

import java.util.regex.Matcher;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import files.UrlValidator;
import files.ResultPair;
import test.UrlValidatorTest;

import files.UrlValidator;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Random;

public class RandomTest extends TestCase {
	@Before
	public void setUp() throws Exception {

	}

	@After
	public void tearDown() throws Exception {
	}
	// get url parts data from UrlValidatorTest class
	ResultPair[] schemes = UrlValidatorTest.testUrlScheme;
	ResultPair[] authorities = UrlValidatorTest.testUrlAuthority;
	ResultPair[] ports = UrlValidatorTest.testUrlPort;
	ResultPair[] paths = UrlValidatorTest.testPath;
	ResultPair[] queries = UrlValidatorTest.testUrlQuery;

	int sLen = schemes.length;
	int aLen = authorities.length;
	int poLen = ports.length;
	int paLen = paths.length;
	int qLen = queries.length;
	@Test
	// test url with <scheme><authority>[<port>][<path>]?<query> (includes query, but port/path optional)
	public void testIncludeQuery() {
		System.out.println();
		long options =
                UrlValidator.ALLOW_2_SLASHES
                    + UrlValidator.ALLOW_ALL_SCHEMES
                    + UrlValidator.NO_FRAGMENTS;
		UrlValidator validator = new UrlValidator(null, null, options);
		Random rand = new Random(); // seed random int generator

	    for(int i=0; i<200; i++) {
	    	String url = ""; // url to build up
			boolean valid = true; // validity boolean to build up

			// get random indices for scheme, port, auth, query arrays
			int s = rand.nextInt(sLen);
			int a = rand.nextInt(aLen);
			int po = rand.nextInt(poLen);
			int pa = rand.nextInt(paLen);
			int q = rand.nextInt(qLen);

			// get scheme
			ResultPair scheme = schemes[s];
			url = url.concat(scheme.item);
			valid = valid && scheme.valid;

			// get authority
			ResultPair authority = authorities[a];
			url = url.concat(authority.item);
			valid = valid && authority.valid;

			// add port if port index is even (to approximate optionality)
			if (po % 2 == 0) {
				ResultPair port = ports[po];
				url = url.concat(port.item);
				valid = valid && port.valid;
			}

	    	// add path if path index is even (to approximate optionality)
			if (pa % 2 == 0) {
				ResultPair path = paths[pa];
				url = url.concat(path.item);
				valid = valid && path.valid;
			}

	    	// add query
			ResultPair query = queries[q];
			url = url.concat(query.item);
			valid = valid && query.valid;
			
			System.out.printf("queryTest\t%d\t%b\t%s\n", i+1, valid, url);
			if(valid) assertTrue(url, validator.isValid(url));
			else assertFalse(url, validator.isValid(url));
	    }
	}
	
	// test url with <scheme><authority><port>[<path>]?<query> (includes port, but query/path optional)
	public void testIncludePort() {
		System.out.println();
        long options =
                UrlValidator.ALLOW_2_SLASHES
                    + UrlValidator.ALLOW_ALL_SCHEMES
                    + UrlValidator.NO_FRAGMENTS;
		UrlValidator validator = new UrlValidator(null, null, options);
		Random rand = new Random(); // seed random int generator

	    for(int i=0; i<200; i++) {
	    	String url = ""; // url to build up
			boolean valid = true; // validity boolean to build up

			// get random indices for scheme, port, auth, query arrays
			int s = rand.nextInt(sLen);
			int a = rand.nextInt(aLen);
			int po = rand.nextInt(poLen);
			int pa = rand.nextInt(paLen);
			int q = rand.nextInt(qLen);

			// get scheme
			ResultPair scheme = schemes[s];
			url = url.concat(scheme.item);
			valid = valid && scheme.valid;

			// get authority
			ResultPair authority = authorities[a];
			url = url.concat(authority.item);
			valid = valid && authority.valid;

			// get port
			ResultPair port = ports[po];
			url = url.concat(port.item);
			valid = valid && port.valid;

	    	// add path if path index is even (to approximate optionality)
			if (pa % 2 == 0) {
				ResultPair path = paths[pa];
				url = url.concat(path.item);
				valid = valid && path.valid;
			}

	    	// add query if query index is even (to approximate optionality)
			if (q % 2 == 0) {
				ResultPair query = queries[q];
				url = url.concat(query.item);
				valid = valid && query.valid;
			}
			System.out.printf("portTest\t%d\t%b\t%s\n", i+1, valid, url);
			if(valid) assertTrue(url, validator.isValid(url));
			else assertFalse(url, validator.isValid(url));
	    }
	}
	// test url with <scheme><authority>[<port>]<path>[?<query>] (includes path, but port/query optional)
	public void testIncludePath() {
		System.out.println();
		long options =
                UrlValidator.ALLOW_2_SLASHES
                    + UrlValidator.ALLOW_ALL_SCHEMES
                    + UrlValidator.NO_FRAGMENTS;
		UrlValidator validator = new UrlValidator(null, null, options);
		Random rand = new Random(); // seed random int generator

	    for(int i=0; i<200; i++) {
	    	String url = ""; // url to build up
			boolean valid = true; // validity boolean to build up

			// get random indices for scheme, port, auth, query arrays
			int s = rand.nextInt(sLen);
			int a = rand.nextInt(aLen);
			int po = rand.nextInt(poLen);
			int pa = rand.nextInt(paLen);
			int q = rand.nextInt(qLen);

			// get scheme
			ResultPair scheme = schemes[s];
			url = url.concat(scheme.item);
			valid = valid && scheme.valid;

			// get authority
			ResultPair authority = authorities[a];
			url = url.concat(authority.item);
			valid = valid && authority.valid;

			// add port if port index is even (to approximate optionality)
			if (po % 2 == 0) {
				ResultPair port = ports[po];
				url = url.concat(port.item);
				valid = valid && port.valid;
			}
			
	    	// add path 
			ResultPair path = paths[pa];
			url = url.concat(path.item);
			valid = valid && path.valid;

	    	// add query if query index is even (to approximate optionality)
			if (q % 2 == 0) {
				ResultPair query = queries[q];
				url = url.concat(query.item);
				valid = valid && query.valid;
			}
			System.out.printf("pathTest\t%d\t%b\t%s\n", i+1, valid, url);
			if(valid) assertTrue(url, validator.isValid(url));
			else assertFalse(url, validator.isValid(url));
	    }
	}

}
