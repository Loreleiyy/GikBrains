function figure(fig) {
    var coord

    switch(fig){
    case "asterisk":{
        coord = [[-7.5, 2.5], [-2.5, 3.5], [0, 8], [2.5, 3.5], [7.5, 2.5],[4, -1],
             [5, -6], [0, -4], [-5, -6], [-4, -1], [-7.5, 2.5]]
    }
    break;
    case "ring":{
        coord = [0, 0, 200, 0, (Math.PI*2)]
    }
    break;
    case "house":{
        coord = [[-5, -5], [-5, 5], [7, 5], [7, -5], [1, -9], [-5, -5], [5, -5]]
    }
    break;
    case "hourglass": {
        coord = [[-5, -5], [0, -5], [-5, 5], [-0, 5], [-5, -5]]
    }
    break;
}
    return coord;
}


