//Variable declarations
const imageForm = document.getElementById('ImageForm');
const imageInput = document.getElementById('FileInput')
const button = document.getElementById('button');

var UserMap = L.map( 'UserMap' ).setView( [0, 0], 1 );

console.log(UserMap.options.maxZoom);

//Set market to invisble on first go
const marker = L.marker( [0,0] ).addTo(UserMap);
marker.setOpacity(0);

const attribution = '&copy; <a href="https://www.openstreetmap.org/copyright"OpenStreetMap</a> contributors';
const tileUrl = 'https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png';
const tiles = L.tileLayer( tileUrl, {attribution} );

let firstTime = true; 


//Add tiles to map
tiles.addTo( UserMap );

//Set div element opacities to 0
document.getElementById("Webcam_failed_text").style.opacity = "0";

//Set input element to opacity 0
document.getElementById("FileInput").style.opacity = "0";

//Set div element opacities to 0
document.getElementById("Image_not_in").style.opacity = "0";  

//Set form element to opacity 0
document.getElementById("ImageForm").style.opacity = "0";  

//Prevent the refresh of page when uploading files
//and uploads data to server
imageForm.addEventListener("change", e => {

	console.log('uploading file');

	e.preventDefault();

	//Creates reqyured destination for file
	const endpoint = "upload.php";
	const formData = new FormData();

	//Send file data to the server
	formData.append("FileInput", imageInput.files[0]);

	console.log(imageInput.files);

	fetch(endpoint, {
		method: "post",
		body: formData
	}).catch(console.error);
});

//Function graphs and sets all data onto the webpage
async function displayData(lat, long)
{
	const latitude = lat;
	const longitude = long;

	//Set latitude and longtitude of marker
	marker.setLatLng( [latitude, longitude] );

	//Change view of map to the user if it's the first time
	//Also make the marker visible
	if  ( firstTime )
	{
		firstTime = false;

		//Set market to visible
		marker.setOpacity(1);


		//Updating view
		UserMap.setView( [latitude, longitude], 20 );
	}
	

	//Set them to the span elements
	document.getElementById( 'latitude' ).textContent = lat.toFixed(2);
	document.getElementById( 'longitude' ).textContent = long.toFixed(2);
}

//This function runs all required client side p5js
//related operations
function setup() 
{	
	noCanvas();

	var createVideo = true;

	var video;
	try{
		video = createCapture(VIDEO);
	}
	catch(error){
		console.log('failed to do the web boi');
		createVideo = false;
	}

	//Set video size
	video.size(320, 240);

	//Load webcam pixels
	video.loadPixels();

	let image = video.get(0, 0, 100, 100); 
	const image64 = image.canvas.toDataURL();

	console.log(image64);


	if( createVideo == false )
	{
		video.pixels[0] = -1;
	}

	//If webcam pixels are not greater than zero
	//There is no webcame device
	if ( video.pixels[0] == -1  )
	{
		//Notify the user their webcam has failed
		document.getElementById("Webcam_failed_text").style.opacity = "1";

		//Allow the user to input an image
		document.getElementById("ImageForm").style.opacity = "1"; 
		document.getElementById("FileInput").style.opacity = "1";
	}

	//In case the text was revealed before
	else
	{

		//Notify the user their webcam has failed
		document.getElementById("Webcam_failed_text").style.opacity = "0";

		//Allow the user to input an image
		document.getElementById("ImageForm").style.opacity = "0"; 
	}

	//This function is called whenever the button is pressed.
	//After the button is pressed it will update the geolocation
	button.addEventListener('click', async event => 
	{
		//Convert image to base 64 if it has pixels
		if ( video == null)
		{
			//Alert the user an image must be loaded
			document.getElementById("Image_not_in").style.opacity = "1";  

			return;
		}

		else
		{
			//Remove the alert if it has already been shown
			document.getElementById("Image_not_in").style.opacity = "0"; 

			video.loadPixels();

			const image64 = video.canvas.toDataURL();

			console.log(image64);

			//Check if the current location is available
			if ( 'geolocation' in navigator )
			{
				console.log( 'geolocation available' );

				navigator.geolocation.getCurrentPosition( async position => 
				{
					//Set latitude and long to the new posistion
					const lat = position.coords.latitude;
					const long = position.coords.longitude;

					//Call function to map user location onto map
					displayData(lat, long);

					//Post data to the server
					const data = { lat, long, image64 };

					//Creates settings for how to post data to server
					const options = {
						method:  'POST',
						headers: {
	      					'Content-Type': 'application/json'
	   					},
						body: JSON.stringify(data)
					};

					//Post the data to the server
					//Also recieve as data for incoming info from the server
					const response = await fetch( '/api', options );

					const json_data = await response.json();

					console.log(json_data);

				});
			}

			else
			{
				console.log( 'geolocation not unavailable' );
			}
		}
	});
}