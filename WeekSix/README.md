This is just a quick document to prove I am proficient working with Javascript and APIs.

For a recent personal project called [Computed Curation](https://philippschmitt.com/projects/computed-curation) I used the [Google Cloud Vision API](https://cloud.google.com/vision/) to retreive tags for image features.

Google actually provides a Javascript library to interact with the API. Under the hood it uses simple POST requests, authenticated by a private token.

Here is a method I created for a class called `VisionService` that uploads a photo file to the service with a range of options. The result triggers a callback function:

```Javascript

VisionService.prototype.detect = function (fileName, callback) {
	var visionClient = vision({
	  keyFilename: '/* file path to private token */',
	  projectId: '151122'
	});

	var options = {
		verbose: true,
		types: [
 			'label',
 			'properties'
 		],
 		maxResults: 10
 	}

 	// actual query to API
	visionClient.detect('../../photos_preview/'+fileName, options, function(err, result) {
	  if (err) console.log(err);
	  callback(null, result);
	});
}

```