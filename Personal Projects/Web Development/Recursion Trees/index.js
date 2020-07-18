const canvas = document.querySelector('canvas');
const generateButton = document.querySelector('.generate-tree-button');

canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

const ctx = canvas.getContext("2d");

function drawTree(startX, startY, len, angle, branchWidth, mainColor, leavesColor )
{
	//Canvas items to create tree, and branches
	ctx.beginPath();
	ctx.save();
	ctx.strokeStyle = mainColor;
	ctx.fillStyle = leavesColor;
	ctx.lineWidth = branchWidth;
	ctx.translate(startX, startY);
	ctx.rotate(angle * Math.PI/180);
	ctx.moveTo(0,0);
	ctx.lineTo(0, -len);
	ctx.stroke();

	//If the length grows past 10, end recursion
	if(len < 10)
	{
		ctx.restore();
		return;
	}

	//Implements recursion, to create fork branches
	drawTree(0, -len * 0.75, angle + 5, branchWidth);
	drawTree(0, -len * 0.75, angle - 5, branchWidth);

	ctx.restore();
}

drawTree( canvas.width/2, canvas.height-80, 120, 0, 2, "brown", "green");