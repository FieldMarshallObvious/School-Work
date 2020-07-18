const canvas = document.querySelector('canvas');
const generateButton = document.querySelector('.generate-tree-button');

canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

const ctx = canvas.getContext('2d');

let curve = ( Math.random() * 10 ) + 10, curve1 = ( Math.random() * 20 ) + 2 , curve2 = ( Math.random() * 50 ) + 1;

drawTree( canvas.width/2, canvas.height-80, 120, 0, 25, 'brown', 'pink');

generateButton.addEventListener('click', generateRandomTree);

function drawTree(startX, startY, len, angle, branchWidth, mainColor, leavesColor )
{
	//Create canvas path
	ctx.beginPath();
	ctx.save();

	//Create stroke colors and shadow
	ctx.strokeStyle = mainColor;
	ctx.fillStyle = leavesColor;
	ctx.lineWidth = branchWidth;
	ctx.shadowBlur = 15;
	ctx.shadowColor = 'rgba(0, 0, 0, 0.5)';

	//Place canvas on certian x and y posistion
	//and rotate canvas to the passed angle
	ctx.translate(startX, startY);
	ctx.rotate(angle * Math.PI/180);

	//Move the tree to the center
	ctx.moveTo(0,0);

	//Create a line to the length
	//ctx.lineTo(0, -len);

	//Curve the tree based on angle
	if( angle > 0 )
	{
		ctx.bezierCurveTo( curve1, -len/2, 10, -len/2, 0, -len );
	}
	else
	{
		ctx.bezierCurveTo( curve2, -len/2, -10, -len/2, 0, -len );
	}

	//Draw the stroke
	ctx.stroke();

	//If the length grows past 10, end recursion
	//and draw leaves
	if(len < 15)
	{
		//Draw leafs
		ctx.beginPath();
		ctx.arc(0, -len, 10, 0, Math.PI/2);
		ctx.fill();

		ctx.restore();


		return;
	}

	//Randomize the curve
	//NOTE uncomment this if you want to make the
	//tree's less symmetrical
	//curve = ( Math.random() * 10 ) + 10;

	//Implements recursion, to create fork branches
	drawTree(0, -len, len * 0.75, angle + curve, branchWidth * 0.6 );
	drawTree(0, -len, len * 0.75, angle - curve, branchWidth * 0.6 );

	ctx.restore();
}

//This function is called when the random tree button is pressed 
function generateRandomTree() {
	ctx.clearRect(0,0,canvas.width, canvas.height);

	//Generate values required to pass to the tree function
	let centerPointX = canvas.width/2;
	let startingPointY = canvas.height - 80;
	let len = Math.floor( (Math.random() * 20) + 100 );
	let angle = 0;
	let branchWidth = (Math.random() * 140) + 1;
	let mainColor = 'rgb(' + Math.random() * 255 + ',' + Math.random() * 255 + ',' + Math.random() * 255 + ')';
	let leavesColor = preventDuplicates(mainColor);


	//Change color of the button to match
	generateButton.style.background = mainColor;

	//Randomize curve of branches
	curve = ( Math.random() * 10 ) + 10
	curve1 = ( Math.random() * 20 ) + 2;
	curve2 = ( Math.random() * 50 ) + 1;

	drawTree(centerPointX, startingPointY, len, angle, branchWidth, mainColor, leavesColor);
}

//This function prevents the branch color
//from being the same as the leaf color
function preventDuplicates( previous )
{
	//Variable declarations
	var output = 'rgb(' + Math.random() * 255 + ',' + Math.random() * 255 + ',' + Math.random() * 255 + ')';

	//While the current color equals this color, try to find a new color
	while( output == previous )
	{
		output = 'rgb(' + Math.random() * 255 + ',' + Math.random() * 255 + ',' + Math.random() * 255 + ')';
	}

	//Return once a new color has been found
	return output;
}
