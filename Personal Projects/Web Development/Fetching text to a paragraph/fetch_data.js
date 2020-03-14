var url = 'Bruh.txt';
var image = 'wow.jpg';


console.log('About to fetch some text');

catchText().catch(error => {
	console.error(error);
});

console.log("About to fetch an image");

catchImage().catch(error => {
	console.error(error);
});

async function catchText() {
	const response = await fetch(url);

	const text = await response.text();

	document.getElementById('passed_text').innerText = text;
}

async function catchImage() {
	const response = await fetch(image);

	const blob = await response.blob();

	document.getElementById('bruh-image').src = URL.createObjectURL(blob);
}