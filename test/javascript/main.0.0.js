"use strict";
// Copyright (c) 2017 Michael Moran

//Animation frame request and clear
(function(){var l=0,v=['webkit','moz'];for(var x=0;x<v.length&&!window.requestAnimationFrame;++x){window.requestAnimationFrame=window[v[x]+'RequestAnimationFrame'];window.cancelAnimationFrame=window[v[x]+'CancelAnimationFrame']||window[v[x]+'CancelRequestAnimationFrame'];}if(!window.requestAnimationFrame)window.requestAnimationFrame=function(callback,element){var c=new Date().getTime(),t=Math.max(0,16-(c-l)),id=window.setTimeout(function(){callback(c+t);},t);l=c+t;return id;};if(!window.cancelAnimationFrame)window.cancelAnimationFrame=function(id){clearTimeout(id);};}());

// DOM
document.body.insertBefore(document.createElement("canvas"),
  document.body.childNodes[0]);
document.body.style.margin = 0;
var
  canvas = document.body.childNodes[0],
  pen = canvas.getContext("2d");
canvas.width = 1280;  // 1920
canvas.height = 720;  // 1080

//Animation frame
var
  FRAME = null,
  ffirst = new Date(),
  fsecond = new Date();
//Keyboard
var
  key = [],  //                   WASD      AROW
  KeyLeft  =  /*space toggle >*/  65,  /*/  37,  /**/
  KeyUp    =  /*              */  87,  /*/  38,  /**/
  KeyRight =  /*              */  68,  /*/  39,  /**/
  KeyDown  =  /*              */  83;  /*/  40;  /**/
// Constants
var
  unit = 10,
  map = {
    width:1600,
    lenght:800,
    draw: function(x,y) {
      pen.beginPath();
      pen.moveTo(canvas.width / 2 - x, canvas.height / 2 - y);
      pen.lineTo(canvas.width / 2 - x, canvas.height / 2 - y + this.lenght);
      pen.lineTo(canvas.width / 2 - x + this.width,
             canvas.height / 2 - y + this.lenght);
      pen.lineTo(canvas.width / 2 - x + this.width, canvas.height / 2 - y);
      pen.lineTo(canvas.width / 2 - x, canvas.height / 2 - y);
      pen.closePath();
      pen.lineWidth = 1;
      pen.strokeStyle = "black";
      pen.stroke();
    },
    bounds:function(x,y,r) {
      r = r | unit;
      return (x - r >= 0) && (x + r <= this.width) &&
             (y - r >= 0) && (y + r <= this.lenght);
    }
  };

// Objects
function Player(x,y) {
  this.x = x | 0;
  this.y = y | 0;
  // this.id = id | 0;
}
Player.prototype.draw = function(){
  map.draw(this.x,this.y);
  pen.beginPath();
  pen.moveTo(canvas.width / 2, canvas.height / 2 - unit);
  pen.lineTo(canvas.width / 2, canvas.height / 2 + unit);
  pen.moveTo(canvas.width / 2 - unit, canvas.height / 2);
  pen.lineTo(canvas.width / 2 + unit, canvas.height / 2);
  pen.closePath();
  pen.lineWidth = 1;
  pen.strokeStyle = "black";
  pen.stroke();
  pen.fillStyle = "black";
  pen.font = "10px Arial";
  pen.fillText(this.x + " " + this.y, canvas.width /2 + unit , canvas.height / 2 - unit);
}

var
  pc = new Player(canvas.width / 2, canvas.height / 2)  // player's character
  ;
  

// Style/CSS
canvas.style.display = 'block';
canvas.style.background = "grey";
document.body.style.background = "black";

// Events
window.onresize = fitWindow;
window.onkeydown = window.onkeyup = keyEvent;


// Functions
function keyEvent(e) {
  e = e || window.Event;
  key[e.keyCode] = e.type === 'keydown';
}
function fitWindow() {
  if (16 * innerHeight > 9 * innerWidth) {  // width based
    canvas.style.margin = (-9 * innerWidth + 16 * innerHeight)/32 + "px 0 0 0";
    canvas.style.width = innerWidth + "px";
    canvas.style.height = 9 * innerWidth / 16 + "px";
  } else if (16 * innerHeight < 9 * innerWidth) {  // height based
    canvas.style.margin = "0 0 0 " +
      (-16 * innerHeight + 9 * innerWidth) / 18 + "px";
    canvas.style.width = 16 * innerHeight /9 + "px";
    canvas.style.height = innerHeight + "px";
  } else {
    canvas.style.margin = "0 0 0 0";
    canvas.style.width = innerWidth + "px";
    canvas.style.height = innerHeight + "px";
  }
}

// Scene
function render() {
  FRAME = window.requestAnimationFrame(render);
  //delete ffirst;
  ffirst = fsecond;
  fsecond = new Date();
  if (key[KeyLeft]) {
    if (map.bounds(pc.x - (fsecond - ffirst) / 2, pc.y))
      pc.x -= (fsecond - ffirst) / 2;
  }
  if (key[KeyUp]) {
    if (map.bounds(pc.x, pc.y - (fsecond-ffirst) / 2))
      pc.y -= (fsecond - ffirst) / 2;
  }
  if (key[KeyRight]) {
    if (map.bounds(pc.x + (fsecond - ffirst) / 2, pc.y))
      pc.x += (fsecond - ffirst) / 2;
  }
  if (key[KeyDown]) {
    if (map.bounds(pc.x, pc.y + (fsecond - ffirst) / 2))
      pc.y += (fsecond - ffirst) / 2;
  }
  pen.clearRect(0, 0, canvas.width, canvas.height);
  pc.draw();
  pen.font = "10px Arial";
  pen.fillStyle = "yellow";
  pen.fillText(parseInt(1000 / (fsecond - ffirst)), 0, 10);
}
// Main
(function() {
  fitWindow();
  FRAME = window.requestAnimationFrame(render);
})();
