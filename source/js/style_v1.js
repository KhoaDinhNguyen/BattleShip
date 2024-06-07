class Ship {
    constructor(name, coor, order) {
        this.name = name;
        this.coor = coor;
        this.cnt = coor.length;
        this.order = order;
    }
    get name() {
        return this.name;
    }
    set name(name) {
        this.name = name;
    }
    get coor() {
        return this.coor;
    }
    set coor(coor) {
        this.coor = coor;
    }
    get cnt() {
        return this.cnt;
    }
    set cnt(cnt) {
        this.cnt = cnt;
    }
    get order() {
        return this.order;
    }
    set order(order) {
        this.order = order;
    }
    rotateShip(rotateNums) {
        let ship_size = this.coor.length;
        for (let i = 0; i < ship_size; i++) {
            for (let j = 1; j <= n; j++) {
                let temp = this.coor[i][0];
                coor[i][0] = coor[i][1];
                coor[i][1] = temp * (-1);
            }
        }
    }
    getHit() {
        this.cnt--;
    }
};

class MotherShip extends Ship {
    constructor(order){
        super("MotherShip", [[0,0],[-1,-1],[-1,1],[1,-1],[1,1]], order);
    }
};

class BattleShip extends Ship {
    constructor(order){
        super("Battleship", [[0,0],[0,1],[1,0],[1,1]], order);
    }
};

class Destroyer extends Ship {
    constructor(order){
        super("Destroyer", [[0,0],[1,-1],[1,1]], order);
    }
};


class StealthShip extends Ship {
    constructor(order){
        super("Stealth ship", [[0,0],[0,1]], order);
    }
};

class PatrolShip extends Ship {
    constructor(order){
        super("Patrol ship", [[0,-1],[0,0],[0,1]], order);
    }
};

/*--------------------------------------------Grid------------------------------------------*/
class Grid {
    constructor(){
        this.isOccupied = false;
        this.isReveal = false;
        this.gridChar = "~";
    }
    set gridChar(letter){
        this.gridChar = letter;
    }
    get gridChar(){
        return this.gridChar;
    }
    set isOccupied(status){
        this.isOccupied = status;
    }
    get isOccupied(){
        return this.isOccupied;
    }
    set isReveal(status){
        this.isReveal = status;
    }
    get isReveal(){
        return this.isReveal;
    }
};

/*--------------------------------------------Map------------------------------------------*/
class LogicMap {
    constructor(shipsNum, xDim, yDim){
        this.shipsArray = new Array(shipsNum.length);
        this.numOfActiveShips = 0;

        for(let i = 0; i < shipsNum.length ; ++i){
            this.shipsArray[i] = shipsNum[i];
            this.numOfActiveShips = this.shipsArray[i] + this.numOfActiveShips;
        }

        this.ships = new Array(this.numOfActiveShips);

        let order = 1, idx = 0, i = 0;
        while(idx < shipsNum.length){
            if(shipsNum[idx] === 0){
                idx++;
                order = 1;
                continue;
            }
            if(idx === 0){
                this.ships[i] = new MotherShip(order);
            }
            else if(idx === 1){
                this.ships[i] = new BattleShip(order)
            }
            else if(idx === 2){
                this.ships[i] = new Destroyer(order);
            }
            else if(idx === 3){
                this.ships[i] = new StealthShip(order);
            }
            else{
                this.ships[i] = new PatrolShip(order);
            }
            i++;
            order++;
            shipsNum[idx]--;
        }

        this.xDim = xDim;
        this.yDim = yDim;
        this.gridMap = new Array(yDim);

        for(let i = 0; i < yDim; ++i){
            this.gridMap[i] = new Array(xDim);
        }

        this.shotToClear = 0;
        for(let i = 0 ; i < this.ships.length; ++i){
            placeShip(this.ships[i]);
            this.shotToClear = this.shotToClear + this.ships[i].cnt;
        }   
    }
    get numOfActiveShips(){
        return this.numOfActiveShips;
    }
    get shotToClear(){
        return this.shotToClear;
    }
    placeShip(ship){
        const shipName = ship.name;
        let validPlacement = false;
        const rotateTime = randomFrom0ToN(3);
        ship.rotateShip(rotateTime);

        let xCenter, yCenter;
        do {
            xCenter = randomFrom0ToN(this.xDim);
            yCenter = randomFrom0ToN(this.yDim);
            validPlacement = this.checkBoundary(xPos, yPos, ship.coor);
        }
        while(!validPlacement);

        const center = [xCenter, yCenter];

        for(let i = 0 ; i < ship.coor.length; ++i){
            ship.coor[i][0] += center[0];
            ship.coor[i][1] += center[0];
            this.gridMap[ship.coor[i][1]][ship.coor[i][0]].gridChar = shipName;
        }

        let minX = ship.coor[0][0], minY = ship.coor[0][1];
        let maxX = ship.coor[0][0], maxY = ship.coor[0][0];

        for(let i = 1; i < ship.coor.length; ++i){
            if(ship.coor[i][0] < minX){
                minX = ship.coor[i][0];
            }
            else if(ship.coor[i][0] > maxX){
                maxX = ship.coor[i][0];
            }

            if(ship.coor[i][1] < minY){
                minY = ship.coor[i][1];
            }
            else if(y > maxY){
                maxY = ship.coor[i][1];
            }
        }

        for(let i = minX; i <= maxX; ++i){
            for(let j = minY; j <= maxY; ++j){
                this.gridMap[j][i].isOccupied = true;
            }
        }

        return;
    }
    checkBoundary(xPos, yPos, shipsCoor){
        let xCoor, yCoor;
        for(const item of shipsCoor){
            xCoor = xPos + item[0];
            yCoor = yPos + item[1];

            if(xCoor < 0 || xCoor >= this.yDim || yCoor < 0 || yCoor >= this.yDim){
                return false;
            }
            if(this.gridMap[yCoor][xCoor].isOccupied){
                return false;
            }
        }

        return true;
    }
    gridShot(x, y){
        if(this.gridMap[y][x].isReveal === true){
            return;
        }
        currentGridChar = this.gridMap[y][x].gridChar;
        if(currentGridChar === "~"){
            console.log("Miss shot");
            this.gridMap[y][x].gridChar("o");
            return 0;
        }
        else if(currentGridChar === "x" || currentGridChar === "o"){
            console.log("The location has already been bombarded!!!");
            return 0;
        }

        this.gridMap[y][x].gridChar = "x";
        for(let i = 0 ; i < this.ships.length; ++i){
            if(this.ships[i].name !== currentGridChar){
                continue;
            }
            if(this.findShipCoor(ships[i], x, y)){
                this.ships[i].getHit();
                if(this.ships[i].cnt === 0){
                    console.log(`DIRECT HIT! \nCongratulation! The enemy ${ships[i].name} has been destroyed!!!`);
                }
                else{
                    console.log(`DIRECT HIT! The shot has landed on enemy ${ships[i].name} ${this.ships[i].order}.`);
                }
                return 1;
            }

        }
        return 1;
    }
    findShipCoor(ship, xPos, yPos){
        shipCoor = ship.coor;

        for(let i = 0; i < shipCoor.length; ++i){
            if(shipCoor[i][0] == xPos && shipCoor[i][1] == yPos){
                return true;
            }
        }
        return false;
    }
    
}

/*======================================== Additional functions ====================================*/
function randomFrom0ToN(n){
    const ran = Math.random();
    if(ran == 1){
        return n;
    }
    return Math.floor(ran * (n + 1));
}
/*============================================ WEB DESIGN ==========================================*/
const board = document.getElementById("board").children[0].children[0];
const fire = document.getElementById("fire");
const restart = document.getElementsByClassName("restart")[0];

const explosion = new Audio("./source/audio/explosion.mp3");

class EventMap {
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

const eventMap = new EventMap();

for(let i = 0 ; i < 10; ++i){
    for(let j = 0; j < 12; ++j){
        eventMap.matrix[i][j] = board.children[i].children[j];
    }
}

let current = undefined;
let func;
let xPos, yPos;
// Function handler for onClickChoose

function chooseCell(event, i, j){
    if(current){
        current.style.backgroundColor = "#04bade";
    }
    event.target.style.backgroundColor = "red";
    current = event.target;
    yPos = i;
    xPos = j;
}

for(let i = 0 ; i < 10; ++i){
    for(let j = 0; j < 12; ++j){
        func = function(event){
            chooseCell(event, i , j);
        }
        eventMap.matrix[i][j].addEventListener("click", func);
    }
}

// Function handler for onClickAttack

function onClickAttack(){
    if(!current) return;
    explosion.pause();
    explosion.currentTime = 0;
    explosion.play();
    current.style.backgroundColor = "grey";
    func = function(event){
        chooseCell(event, yPos , xPos);
    }
    current.removeEventListener("click", func);
    current = undefined;
}

fire.addEventListener("click", onClickAttack);

// Function handler for restart

function onClickRestart(){
    location.reload();
}

restart.addEventListener("click", onClickRestart);