function createSimpleTable(tx) {
    const sql = 'CREATE TABLE IF NOT EXISTS contacts (' +
              'contact_id INTEGER PRIMARY KEY,' +
              'first_name TEXT NOT NULL,' +
              'last_name TEXT NOT NULL,' +
              'email TEXT NOT NULL UNIQUE,' +
              'phone TEXT NOT NULL UNIQUE' +
              ');'
    tx.executeSql(sql)
    console.log("createSimpleTable")

}

function createSimpleTable2(tx) {
    const sql = 'CREATE TABLE IF NOT EXISTS friend (' +
              'id INTEGER PRIMARY KEY,' +
              'name TEXT NOT NULL,' +
              'surname TEXT NOT NULL,' +
              'friends TEXT NOT NULL' +
              ');'
    tx.executeSql(sql)
    console.log("createSimpleTable2")

}

function addContact(tx, first_name, last_name, email, phone){
    console.log("addContact")
    const sql = 'INSERT INTO contacts (first_name, last_name, email, phone)' +
              'VALUES("%1", "%2", "%3", "%4");'.arg(first_name).arg(last_name).arg(email).arg(phone);

    console.log(sql)
    return tx.executeSql(sql)
}

function addContact2(tx, name, surname, friends){
    console.log("addContact")
    const sql = 'INSERT INTO friend (name, surname, friends)' +
              'VALUES("%1", "%2", "%3");'.arg(name).arg(surname).arg(friends)

    console.log(sql)
    return tx.executeSql(sql)
}

function readContacts(tx){

    const sql = 'SELECT * FROM contacts'
    var res = tx.executeSql(sql)

    for(var i = 0; i < res.rows.length; ++i){
        _model1.appendRow({id: res.rows.item(i).contact_id,
                        first_name: res.rows.item(i).first_name,
                        last_name: res.rows.item(i).last_name,
                        email: res.rows.item(i).email,
                        phone: res.rows.item(i).phone
                        })
        //console.log(res.rows.item(i).phone)
        //console.log(_model1.getRow(i).first_name)
    }

    console.log("getContact")
}

function readContacts2(tx){

    const sql = 'SELECT * FROM friend'
    var res = tx.executeSql(sql)

    for(var i = 0; i < res.rows.length; ++i){
        _model2.appendRow({rowid: res.rows.item(i).id,
                        name: res.rows.item(i).name,
                        surname: res.rows.item(i).surname,
                        friends: res.rows.item(i).friends,
                        })
        //console.log(res.rows.item(i).surname)

    }

    //console.log("getContact2")
}

function setContact(tx, db, id, col, data){
    console.log("setContsct")
    const sql = 'UPDATE "main"."%1" SET "%2"="%3" WHERE "_rowid_"="%4"'.arg(db).arg(col).arg(data).arg(id);
    console.log(sql);
    tx.executeSql(sql)
}
