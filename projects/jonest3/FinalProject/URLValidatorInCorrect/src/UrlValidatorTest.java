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
	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
   }
   
   
   public void testIsValid()
   {
	ArrayList<String> schemeArray
	ArrayList<String> hostArray
	ArrayList<String> portArray
	ArrayList<String> pathArray
	ArrayList<String> queryArray

	String testURL;

	for (String scheme : schemeArray) {
		for (String host : hostArray) {
			for (String port : portArray) {
				for (String path : pathArray) {
					for (String query : queryArray) {
						testURL = "";
						testURL = scheme + host + port + path + query;
						System.out.println(testURL);
						System.out.print(urlVal.isValid(testURL));
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
   

}
