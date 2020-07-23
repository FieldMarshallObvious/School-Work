var elements;
var windowHeight;

function init() {
  elements = document.querySelectorAll('.untouched');
  windowHeight = window.innerHeight;

  console.log(windowHeight);

  if( elements.length == 0 )
  {
    elements = document.querySelectorAll('.appearance');
    windowHeight = window.innerHeight;
  }
}

function checkPosition() {
  for (var i = 0; i < elements.length; i++) {
    var element = elements[i];
    var elementClass = elements[i].className;
    var positionFromTop = elements[i].getBoundingClientRect().top;

    var appearTrue = positionFromTop - (windowHeight - windowHeight*0.16) <= 0;
    var disappearTrue = positionFromTop*0.2 + windowHeight >= windowHeight*0.11 + windowHeight && elementClass.slice(elementClass.search('appearance'), elementClass.length) == 'appearance';

    console.log(positionFromTop);
    console.log("posistion from top", positionFromTop + (positionFromTop * 0.2));
    console.log("Top windowHeight is ", windowHeight*0.15 - windowHeight);
    console.log("The sum is ", positionFromTop*0.2 + windowHeight);
    console.log("Is ready to be removed ", disappearTrue);
    console.log("The classname is, ",  elementClass.slice(elementClass.search('appearance'), elementClass.length));

    if ( appearTrue ) {
      element.classList.add('appearance');
      element.classList.remove('untouched');
    }

    if ( disappearTrue )
    {
      console.log("Disappearing");
      element.classList.remove('appearance');
      element.classList.add('untouched');
    }
  }
}


init();
checkPosition();

window.addEventListener('scroll', checkPosition);
window.addEventListener('resize', init);