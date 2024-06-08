class Ship {
    constructor(name, coor, order) {
        this._name = name;
        this._coor = coor;
        this._cnt = coor.length;
        this._order = order;
    }
    get name() {
        return this._name;
    }
    get coor() {
        return this._coor;
    }
    set coor(coor) {
        this._coor = coor;
    }
    get cnt() {
        return this._cnt;
    }
    set cnt(cnt){
        this._cnt = cnt;
    }
    get order() {
        return this._order;
    }
    rotateShip(rotateNums) {
        let shipSize = this._coor.length;
        for (let i = 0; i < shipSize; ++i) {
            for (let j = 0; j < rotateNums; ++j) {
                let temp = this.coor[i][0];
                this.coor[i][0] = this.coor[i][1];
                this.coor[i][1] = temp * -1;
            }
        }
    }
    getHit() {
        this.cnt--;
    }
}

class MotherShip extends Ship {
    constructor(order) {
        super(
            "MotherShip",
            [
                [0, 0],
                [-1, -1],
                [-1, 1],
                [1, -1],
                [1, 1],
            ],
            order
        );
    }
}

class BattleShip extends Ship {
    constructor(order) {
        super(
            "Battleship",
            [
                [0, 0],
                [0, 1],
                [1, 0],
                [1, 1],
            ],
            order
        );
    }
}

class Destroyer extends Ship {
    constructor(order) {
        super(
            "Destroyer",
            [
                [0, 0],
                [1, -1],
                [1, 1],
            ],
            order
        );
    }
}

class StealthShip extends Ship {
    constructor(order) {
        super(
            "Stealth ship",
            [
                [0, 0],
                [0, 1],
            ],
            order
        );
    }
}

class PatrolShip extends Ship {
    constructor(order) {
        super(
            "Patrol ship",
            [
                [0, -1],
                [0, 0],
                [0, 1],
            ],
            order
        );
    }
}

/*--------------------------------------------Grid------------------------------------------*/
class Grid {
    constructor() {
        this._isOccupied = false;
        this._isReveal = false;
        this._gridType = "~";
    }
    set gridType(name) {
        this._gridType = name;
    }
    get gridType() {
        return this._gridType;
    }
    set isOccupied(status) {
        this._isOccupied = status;
    }
    get isOccupied() {
        return this._isOccupied;
    }
    set isReveal(status) {
        this._isReveal = status;
    }
    get isReveal() {
        return this._isReveal;
    }
}

/*--------------------------------------------Map------------------------------------------*/
class LogicMap {
    constructor(shipsNum, xDim, yDim) {
        this._numOfActiveShips = 0;

        for (let i = 0; i < shipsNum.length; ++i) {
            this.numOfActiveShips = shipsNum[i] + this.numOfActiveShips;
        }

        this._ships = new Array();

        let order = 1,
            idx = 0;
        while (idx < shipsNum.length) {
            if (shipsNum[idx] === 0) {
                idx++;
                order = 1;
                continue;
            }
            if (idx === 0) {
                this.ships.push(new MotherShip(order));
            } else if (idx === 1) {
                this.ships.push(new BattleShip(order));
            } else if (idx === 2) {
                this.ships.push(new Destroyer(order));
            } else if (idx === 3) {
                this.ships.push(new StealthShip(order));
            } else {
                this.ships.push(new PatrolShip(order));
            }
            order++;
            shipsNum[idx]--;
        }

        this._xDim = xDim;
        this._yDim = yDim;
        this._gridMap = new Array();

        for (let i = 0; i < yDim; ++i) {
            const rows = new Array();
            for (let j = 0; j < xDim; ++j) {
                rows.push(new Grid());
            }
            this.gridMap.push(rows);
        }

        this._shotToClear = 0;
        for (let i = 0; i < this.ships.length; ++i) {
            this.placeShip(this.ships[i]);
            this.shotToClear = this.shotToClear + this.ships[i].cnt;
        }
    }
    get ships() {
        return this._ships;
    }
    set ships(ships) {
        this._ships = ships;
    }
    get numOfActiveShips() {
        return this._numOfActiveShips;
    }
    set numOfActiveShips(numOfActiveShips) {
        this._numOfActiveShips = numOfActiveShips;
    }
    get shotToClear() {
        return this._shotToClear;
    }
    set shotToClear(shotToClear) {
        this._shotToClear = shotToClear;
    }
    get gridMap() {
        return this._gridMap;
    }
    get xDim() {
        return this._xDim;
    }
    get yDim() {
        return this._yDim;
    }
    placeShip(ship) {
        const shipName = ship.name;
        let validPlacement = false;
        const rotateTime = randomFrom0ToN(3);
        ship.rotateShip(rotateTime);

        let xCenter, yCenter;
        do {
            xCenter = randomFrom0ToN(this.xDim);
            yCenter = randomFrom0ToN(this.yDim);
            validPlacement = this.checkBoundary(xCenter, yCenter, ship.coor);
        } while (!validPlacement);

        const center = [xCenter, yCenter];

        for (let i = 0; i < ship.coor.length; ++i) {
            ship.coor[i][0] += center[0];
            ship.coor[i][1] += center[1];
            this.gridMap[ship.coor[i][1]][ship.coor[i][0]].gridType = shipName;
        }

        let minX = ship.coor[0][0],
            minY = ship.coor[0][1];
        let maxX = ship.coor[0][0],
            maxY = ship.coor[0][1];

        for (let i = 1; i < ship.coor.length; ++i) {
            if (ship.coor[i][0] < minX) {
                minX = ship.coor[i][0];
            } else if (ship.coor[i][0] > maxX) {
                maxX = ship.coor[i][0];
            }

            if (ship.coor[i][1] < minY) {
                minY = ship.coor[i][1];
            } else if (ship.coor[i][1] > maxY) {
                maxY = ship.coor[i][1];
            }
        }

        for (let i = minX; i <= maxX; ++i) {
            for (let j = minY; j <= maxY; ++j) {
                this.gridMap[j][i].isOccupied = true;
            }
        }

        return;
    }
    checkBoundary(xPos, yPos, shipsCoor) {
        let xCoor, yCoor;
        for (const item of shipsCoor) {
            xCoor = xPos + item[0];
            yCoor = yPos + item[1];

            if (xCoor < 0 || xCoor >= this.yDim || yCoor < 0 || yCoor >= this.yDim) {
                return false;
            }
            if (this.gridMap[yCoor][xCoor].isOccupied) {
                return false;
            }
        }

        return true;
    }
    gridShot(x, y) {
        if (this.gridMap[y][x].isReveal === true) {
            return;
        }
        this.gridMap[y][x].isReveal = true;
        const currentGridChar = this.gridMap[y][x].gridType;
        if (currentGridChar === "~") {
            return false;
        }

        this.gridMap[y][x].gridType = "x";
        for (let i = 0; i < this.ships.length; ++i) {
            if (this.ships[i].name !== currentGridChar) {
                continue;
            }
            if (this.findShipCoor(this.ships[i], x, y)) {
                this.ships[i].getHit();
                if (this.ships[i].cnt === 0) {
                    this.numOfActiveShips--;
                    console.log(
                        `DIRECT HIT! \nCongratulation! The enemy ${this.ships[i].name} has been destroyed!!!`
                    );
                } else {
                    console.log(
                        `DIRECT HIT! The shot has landed on enemy ${this.ships[i].name} ${this.ships[i].order}.`
                    );
                }
                return true;
            }
        }
        return true;
    }
    findShipCoor(ship, xPos, yPos) {
        const shipCoor = ship.coor;

        for (let i = 0; i < shipCoor.length; ++i) {
            if (shipCoor[i][0] == xPos && shipCoor[i][1] == yPos) {
                return true;
            }
        }
        return false;
    }
}

const logicMap = new LogicMap([1, 1, 1, 1, 1], 12, 10);
/*======================================== Additional functions ====================================*/
function randomFrom0ToN(n) {
    const ran = Math.random();
    if (ran == 1) {
        return n;
    }
    return Math.floor(ran * (n + 1));
}

/*============================================ WEB DESIGN ==========================================*/
const board = document.getElementById("board").children[0].children[0];
const fire = document.getElementById("fire");
const restart = document.getElementsByClassName("restart")[0];
const announce = document.getElementsByClassName("info")[0];

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
    if (current) {
        current.style.backgroundColor = "#04bade";
        current.style.position = "static";
        current.style.border = "white solid 2px";
    event.target.style.borderRight = "solid 2px rgba(0, 0, 255, .5)";
    } else if (logicMap.gridMap[y][x].isReveal) {
        return;
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
    current.style.backgroundColor = "grey";
    current.style.position = "static";
    current.style.border = "white solid 2px";
    func = function (event) {
        chooseCell(event, yPos, xPos);
    };
    current.removeEventListener("click", func);
    current = undefined;
    const isHit = logicMap.gridShot(xPos, yPos);
    const info = document.createElement('p');
    info.id = 'hit';
   
    if(isHit){
        info.innerHTML = 'HIT!';
        info.style.color = "yellow";
    }
    else{
        info.innerHTML = 'MISS';
        info.style.color = "#e93b3b";
    }
    announce.appendChild(info);
    setTimeout(() => {
        announce.removeChild(info);
    }, 1000)
}

fire.addEventListener("click", onClickAttack);

// Function handler for restart

function onClickRestart() {
    location.reload();
}

restart.addEventListener("click", onClickRestart);
