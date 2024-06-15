import {resources} from './logic'

const {Ship, Grid, LogicMap, randomFrom0ToN} = resources;

const logicMap = new LogicMap([1, 1, 1, 1, 1], 12, 10);
let msg;
let numberOfFired = 0;

/*============================================ WEB DESIGN ==========================================*/
const board = document.getElementById("board").children[0].children[0];
const fire = document.getElementById("fire");
const restart = document.getElementsByClassName("restart")[0];
const announce = document.getElementsByClassName("info")[0];
const logList = document.getElementById("logFileList");
const shipShape = document.getElementsByClassName("shipShape")[0];
const shipShapeButton = document.getElementsByClassName("shipShapeButton")[0];

const explosion = new Audio("./source/audio/explosion.mp3");

class EventMap {
    constructor() {
        this._matrix = new Array();
        for (let i = 0; i < 10; ++i) {
            const rows = new Array(12);
            this.matrix.push(rows);
        }
    }
    get matrix() {
        return this._matrix;
    }
    set matrix(matrix) {
        this._matrix = matrix;
    }
    getCell(i, j) {
        return this.matrix[i][j];
    }
}

const eventMap = new EventMap();

for (let i = 0; i < 10; ++i) {
    for (let j = 0; j < 12; ++j) {
        eventMap.matrix[i][j] = board.children[i].children[j];
    }
}

let current = undefined;
let func;
let xPos, yPos;
// Function handler for onClickChoose

function chooseCell(event, y, x) {
    if (logicMap.gridMap[y][x].isReveal) {
        return;
    }
    else if (current) {
        current.style.backgroundColor = "#04bade";
        current.style.position = "static";
        current.style.border = "white solid 2px";
    event.target.style.borderRight = "solid 2px rgba(0, 0, 255, .5)";
    } 
    event.target.style.backgroundColor = "red";
    event.target.style.position = "relative";
    event.target.style.bottom = "5px";
    event.target.style.borderBottom = "solid 2px rgba(0, 0, 255, .5)";
    event.target.style.borderRight = "solid 2px rgba(0, 0, 255, .5)";
    
    current = event.target;
    yPos = y;
    xPos = x;
}

for (let i = 0; i < 10; ++i) {
    for (let j = 0; j < 12; ++j) {
        func = function (event) {
            chooseCell(event, i, j);
        };
        eventMap.matrix[i][j].addEventListener("click", func);
    }
}

// Function handler for onClickAttack
function onClickAttack() {
    if(announce.children.length === 2){
        announce.removeChild(document.getElementById('hit'));
    }
    if (!current) return;
    explosion.pause();
    explosion.currentTime = 0;
    explosion.play();
    current.style.position = "static";
    current.style.border = "white solid 2px";
    func = function (event) {
        chooseCell(event, yPos, xPos);
    };
    current.removeEventListener("click", func);
    const isHit = logicMap.gridShot(xPos, yPos);
    const info = document.createElement('p');
    info.id = 'hit';
   
    if(isHit){
        current.style.backgroundColor = "#50F76C";
        info.innerHTML = 'HIT!';
        info.style.color = "yellow";
    }
    else{
        info.innerHTML = 'MISS';
        info.style.color = "#e93b3b";
        current.style.backgroundColor = "grey";
    }
    current = undefined;

    announce.appendChild(info);

    setTimeout(() => {
        if(announce.children.length == 2){
            announce.removeChild(info);
        }
    }, 1000);

    // Log file
    const listItem = document.createElement('li');
    const content = document.createElement('p');
    content.innerHTML = msg;
    listItem.appendChild(content);
    logList.appendChild(listItem);
    numberOfFired++;
    document.getElementsByClassName("shoot")[0].children[0].children[0].innerHTML = `<span>${numberOfFired}</span>`;
    document.getElementsByClassName("shoot")[0].children[1].children[0].innerHTML = `<span>${logicMap.shotToClear}</span>`;
    document.getElementsByClassName("shoot")[0].children[2].children[0].innerHTML = `<span>${logicMap.numOfActiveShips}</span>`;

}

fire.addEventListener("click", onClickAttack);

// Function handler for restart

function onClickRestart() {
    location.reload();
}

restart.addEventListener("click", onClickRestart);

// Function handler for ship shapes

function mouseEnterShipShape(){
    shipShape.style.visibility = "visible";
}

function mouseLeaveShipShape(){
    shipShape.style.visibility = "hidden";
}

shipShapeButton.addEventListener("mouseenter", mouseEnterShipShape);
shipShapeButton.addEventListener("mouseleave", mouseLeaveShipShape);

document.getElementsByClassName("shoot")[0].children[0].children[0].innerHTML = `<span>${numberOfFired}</span>`;
document.getElementsByClassName("shoot")[0].children[1].children[0].innerHTML = `<span>${logicMap.shotToClear}</span>`;
document.getElementsByClassName("shoot")[0].children[2].children[0].innerHTML = `<span>${logicMap.numOfActiveShips}</span>`;