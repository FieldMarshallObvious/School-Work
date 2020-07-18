const canvas = document.querySelector('canvas');
const generateButton = document.querySelector('.generate-tree-button');

canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

const ctx = canvas.getContext('2d');

function drawTree(startX, startY, len, angle, branchWidth, mainColor, leavesColor )
{
	//Create canvas path
	ctx.beginPath();
	ctx.save();

	//Create stroke colors
	ctx.strokeStyle = mainColor;
	ctx.fillStyle = leavesColor;
	ctx.lineWidth = branchWidth;

	//Place canvas on certian x and y posistion
	//and rotate canvas to the passed angle
	ctx.translate(startX, startY);
	ctx.rotate(angle * Math.PI/180);

	//Move the tree to the center
	ctx.moveTo(0,0);

	//Create a line to the length
	ctx.lineTo(0, -len);

	//Draw the stroke
	ctx.stroke();

	//If the length grows past 10, end recursion
	if(len < 10)
	{
		//Pops last entry in drawing stack
		ctx.restore();
		return;
	}

	//Implements recursion, to create fork branches
	drawTree(0, -len, len * 0.75, angle + 5, branchWidth, mainColor, leavesColor);
	drawTree(0, -len, len * 0.75, angle - 5, branchWidth, mainColor, leavesColor);

	ctx.restore();
}

drawTree( canvas.width/2, canvas.height-80, 120, 0, 2, 'brown', 'green');