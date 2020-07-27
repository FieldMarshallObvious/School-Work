//Get drawing tools
const canvas = document.getElementById('canvas1');
const ctx = canvas.getContext('2d');
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

//Variable declarations
const edge = 200;
let hue = 0;
let drawing = false;
const mouse = {
	x: 0,
	y: 0,
};

//Update mouse posistion when it moves
window.addEventListener('mousemove', function(e){
	mouse.x = event.x;
	mouse.y = event.y;
});

//This class creates root
//object
class Root
{
	constructor(x, y, color, centerX, centerY, hue)
	{
		this.x = x;
		this.y = y;
		this.color = 'hsl(' + hue + ', 100%, 50%)';
		this.stroke ='hsl(' + ( hue + 20 )  + ', 100%, 50%)';
		this.speedX = 0;
		this.speedY = 0;
		this.centerX = centerX;
		this.centerY = centerY;
	}

	//This function draws roots
	draw()
	{

		//Create speeds for roots
		this.speedX += (Math.random() - 0.5) / 2;
		this.speedY += (Math.random() - 0.5) / 2;

		this.x += this.speedX;
		this.y += this.speedY;

		//Calculate distance of root particle
		//from cetner
		const distanceX = this.x - this.centerX;
		const distanceY = this.y - this.centerY;
		const distance = Math.sqrt(distanceX * distanceX + distanceY * distanceY);

		//Calculate current size of the particle
		const radius = (-distance / edge + 1) * edge / 10;


		//If the radius has not reached the edge
		if( radius > 0 )
		{

			requestAnimationFrame(this.draw.bind(this));

			//Draw each particle
			ctx.beginPath();
			ctx.arc(this.x, this.y, radius, 0, 2 * Math.PI);
			ctx.fillStyle = this.color;
			ctx.fill();
			ctx.strokeStyle = this.stroke;
			ctx.stroke();
		}
	}
}


//This function creates stems that
//branch out from mouse
function branchOut()
{
	if( drawing == true )
	{
		const centerX = mouse.x;
		const centerY = mouse.y;

		//Draw roots from center
		for( let i = 0; i < 30; i++ )
		{
			//Create root
			const root = new Root(mouse.x, mouse.y, 'green', centerX, centerY, hue);
			//x, y, color, centerX, centerY

			//Draw root
			root.draw();

			hue+=2;
		}
	}
}


branchOut();

//Listen for window changing size, to reset values
window.addEventListener( 'resize', function() {
	canvas.width = window.innerWidth;
	canvas.height = window.innerHeight;
});

window.addEventListener( 'mousemove', function() {
	//ctx.fillStyle = 'rgba(255, 255, 255, 0.3)';
	//ctx.clearRect( 0, 0, canvas.width, canvas.height);

	branchOut();
});

//Listen for every mouse click
window.addEventListener( 'mousedown', function(event) {
	
	//If the middle mouse button is clicked,
	//clear the canvas
	if( event.which == 2 )
	{
		ctx.fillStyle = 'rgba(255, 255, 255, 0.3)';
		ctx.clearRect( 0, 0, canvas.width, canvas.height);
		drawing = false;
	}
	else
		drawing = true;
});

//Listen for whenever the mouse is no longer being clicked
window.addEventListener( 'mouseup', function() {
	drawing = false;
});