/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   ResultPair[] urlArray = {new ResultPair ("http://www.amazon.com", true),	
			   					new ResultPair ("http://www.ludlums.com", true),
			   					new ResultPair ("http://.ludlums.com", false),
			   					new ResultPair ("http:/www.ludlums.com", false),
			   					new ResultPair ("http//www.ludlums.com", false),
			   					new ResultPair ("http://ludlums.com/component/virtuemart/general-purpose-ratemeter-detail", true),
			   					new ResultPair ("http://ludlums.com/component/virtuemart/general-purpose-ratemeter-detail?activetab=introduction&Itemid=2657", true),
			   					new ResultPair ("http://ludlums.com/products//general-purpose-meters/ratemeter", true),
			   					new ResultPair ("http://oregonstate.edu", true),	
			   					new ResultPair ("http://eljentechnology.com", true),
			   					new ResultPair ("http://ludlums.com/../", false),
			   					new ResultPair ("http://ludlums.com/component/virtuemart/..?activetab=introduction", true)};

	   for(ResultPair url : urlArray){
		System.out.println(url.item + " Expected: " + url.valid + " Result: " + urlVal.isValid(url.item));
	   }
/*
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   System.out.println(urlVal.isValid("http://www.ludlums.com"));
	   System.out.println(urlVal.isValid("http://.ludlums.com"));
	   System.out.println(urlVal.isValid("http:/www.ludlums.com"));
	   System.out.println(urlVal.isValid("http//www.ludlums.com"));
	   System.out.println(urlVal.isValid("http://ludlums.com/component/virtuemart/general-purpose-ratemeter-detail"));
	   System.out.println(urlVal.isValid("http://ludlums.com/component/virtuemart/general-purpose-ratemeter-detail?activetab=introduction&Itemid=2657")); //returns false when it should be true
	   System.out.println(urlVal.isValid("http://ludlums.com/products//general-purpose-meters/ratemeter"));
	   System.out.println(urlVal.isValid("http://oregonstate.edu"));
	   System.out.println(urlVal.isValid("http://eljentechnology.com"));
	   System.out.println(urlVal.isValid("http://ludlums.com/../"));
	   System.out.println(urlVal.isValid("http://ludlums.com/component/virtuemart/..?activetab=introduction"));
*/	   
	   System.out.println();
   }
   

   // Testing invalid host
   public void testhost(){
	System.out.println("** Testing host **");
	UrlValidator url = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	ResultPair testPair;
	boolean expected;
	boolean result;

	for(ResultPair host : hostArray){
		testPair = host;
		expected = host.valid;
		result = url.isValid("http://" + testPair.item);
		if(expected != result)
			System.out.println("failed - " + testPair.item + "  (expected: " + testPair.valid + "  result: " + result + ")");
		else
			System.out.println("passed - " + testPair.item + "  (expected: " + testPair.valid + "  result: " + result + ")");
	}
	System.out.println();
   }
   
   public void testQuery(){
	System.out.println("** Testing Query **");
	UrlValidator url = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	ResultPair testPair;
	boolean expected;
	boolean result;

	for(ResultPair query : queryArray){ 
		testPair = query;
		expected = query.valid;		
		result = url.isValid("http://google.com/" + testPair.item);
		if(expected != result)
			System.out.println("failed - " + testPair.item + "  (expected: " + testPair.valid + "  result: " + result + ")");
		else
			System.out.println("passed - " + testPair.item + "  (expected: " + testPair.valid + "  result: " + result + ")");
	}
	System.out.println();
   }

   public void testScheme(){
	System.out.println("** Testing Scheme **");
	UrlValidator url = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	ResultPair testPair;
	boolean expected;
	boolean result;

	for(ResultPair scheme : schemeArray){
		testPair = scheme;
		expected = scheme.valid;
		result = url.isValid(testPair.item + "www.google.com");
		if(expected != result)
			System.out.println("failed - " + testPair.item + "  (expected: " + testPair.valid + "  result: " + result + ")");
		else
			System.out.println("passed - " + testPair.item + "  (expected: " + testPair.valid + "  result: " + result + ")");
	}
	System.out.println();
   }

   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
   }
   
   
   public void testIsValid(ResultPair[] schemeArray, ResultPair[] hostArray, ResultPair[] portArray, ResultPair[] pathArray, ResultPair[] queryArray)
   {
	UrlValidator url = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	String testURL;

	boolean expectedResult = true;
	boolean testedResult;
	//int errorCount = 0;
	
	String scheme, host, port, path, query;

	for (ResultPair s : schemeArray) {
		scheme = s.item;
		for (ResultPair h : hostArray) {
			host = h.item;
			for (ResultPair po : portArray) {
				port = po.item;
				for (ResultPair pa : pathArray) {
					path = pa.item;
					for (ResultPair q : queryArray) {
						query = q.item;

						if(!s.valid  ||  !h.valid  ||  !po.valid  ||  !pa.valid  ||  !q.valid)
							expectedResult = false;

						testURL = "";
						testURL = scheme + host + port + path + query;
						System.out.println(testURL);
						testedResult = url.isValid(testURL);
						System.out.print(testedResult);
						
						if(testedResult != expectedResult){
							System.out.println("- TEST FAILED: " + scheme + host + port + path + query);
							//errorCount++;

/*
							// error in query
							if(errorCount == 1){
								System.out.println("Error in QUERY");
							}
							// error in path
							else if(errorCount == queryArray.length){
								System.out.println("Error in PATH");
							}
							// error in port
							else if(errorCount == (queryArray.length * pathArray.length)){
								System.out.println("Error in PORT");
							}	
							// error in host
							else if(errorCount == (queryArray.length * pathArray.length * portArray.length)){
								System.out.println("Error in HOST");
							}
							// error in scheme
							else if(errorCount == (queryArray.length * pathArray.length * portArray.length * hostArray.length)){
								System.out.println("Error in SCHEME");
							}
							else{
								System.out.println("****ERROR IN DEBUGGING LOGIC****");
							}
*/
						}
						else
							System.out.println("+ TEST PASSED");
					}
				}
			}
		}
	}
	for(int i = 0;i<10000;i++)
	{
		   
	}
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   
   ResultPair[] schemeArray = {
	new ResultPair("", true),
	new ResultPair("http://", true),
	new ResultPair("https://", true),
	new ResultPair("http//", false),
	new ResultPair("http:/", false),
	new ResultPair("http:", false),
	new ResultPair("ftp://", true),
	new ResultPair("://", false),
	new ResultPair("123://", false),
	new ResultPair("5http://", false),
	new ResultPair("&*&://", false),
	new ResultPair("//", false),
	new ResultPair(":", false)
   };   

   ResultPair[] hostArray = {
	new ResultPair("", false),
	new ResultPair("google.com", true),
	new ResultPair("amazon.com", true),
	new ResultPair("ludlums.com", true),
	new ResultPair("google.co.uk", true),
	new ResultPair("google.uk", true),
	new ResultPair("google.com.br", true),
	new ResultPair("www.google.com", true),
	new ResultPair("0.0.0.0", true),
	new ResultPair("255.255.255.255", true),
	new ResultPair("abc.123", false),
	new ResultPair("123.abc", false)
   }; 

   ResultPair[] portArray = {
	new ResultPair("", true),
	new ResultPair(":0", true),
	new ResultPair(":1", true),
	new ResultPair(":-1", false),
	new ResultPair(":99999", true),
	new ResultPair(":abcd", false),
	new ResultPair(":123abc", false),
	new ResultPair(":", false)	
   };

   ResultPair[] pathOptionsArray = {
	new ResultPair("", true),
	new ResultPair("/#", false),
	new ResultPair("/..", false),
	new ResultPair("/../abc", false),
	new ResultPair("/123/abc", true),
	new ResultPair("/..//abc", false),
	new ResultPair("/123//abc", true)
   };

   ResultPair[] queryArray = {
	new ResultPair("", true),
	new ResultPair("?foo=bar", true),
	new ResultPair("?foo=bar&bar=foo", true),
	new ResultPair("?q=%5E(.*)%24", true),
	new ResultPair("search?q=pickle", true),
	new ResultPair("search?q=%5E(.*)%24rlz=1C1CHBF_enUS771US771&oq=%5E(.*)%24&aqs=chrome..69i57j0.713j0j4&sourceid=chrome&ie=UTF-8",true),
	new ResultPair("search?", true),
	new ResultPair("?", true)
   };
}
