const board = document.getElementById("board").children[0].children[0];
const fire = document.getElementById("fire");
const restart = document.getElementsByClassName("restart")[0];

class Map {
    constructor(){
        this.matrix = new Array(10);
        for(let i = 0; i < 10; ++i){
            this.matrix[i] = new Array(12);
        }
    }
    getCell(i , j){
        return this.matrix[i][j];
    }
}

const eventMap = new Map();

for(let i = 0 ; i < 10; ++i){
    for(let j = 0; j < 12; ++j){
        eventMap.matrix[i][j] = board.children[i].children[j];
    }
}

let current = undefined;

// Function handler for onClickChoose
function onClickChoose(event){
    if(current){
        current.style.backgroundColor = "#04bade";
    }
    event.target.style.backgroundColor = "red";
    current = event.target;
}

for(let i = 0 ; i < 10; ++i){
    for(let j = 0; j < 12; ++j){
        eventMap.matrix[i][j].addEventListener("click", onClickChoose);
    }
}

// Function handler for onClickAttack

function onClickAttack(){
    if(!current) return;
    current.style.backgroundColor = "grey";
    current.removeEventListener("click", onClickChoose);
    current = undefined;
}

fire.addEventListener("click", onClickAttack);

// Function handler for restart

function onClickRestart(){
    location.reload();
}

restart.addEventListener("click", onClickRestart);