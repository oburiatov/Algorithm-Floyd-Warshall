const express = require('express');
const app = express()
const cors = require('cors');
app.use(cors());
app.use(express.static('public'));
const PORT = 30501


var fs = require('fs');
var https = require('https');
var privateKey  = fs.readFileSync('/app/ssl/devopseek.key', 'utf8');
var certificate = fs.readFileSync('/app/ssl/devopseek.crt', 'utf8');
var credentials = {key: privateKey, cert: certificate};
var httpsServer = https.createServer(credentials, app);

httpsServer.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`)
});

let loadOption = "gen";
let topFrom = "NULL";
let topTo = "NULL";
let topsNum = "NULL";
let programType = "NULL";

// app.listen(PORT, () => {
//     console.log(`Server running on port ${PORT}`)
// })

const multer = require("multer");

var storage = multer.diskStorage({
    destination: function (req, file, cb) {
      cb(null, '.')
    },
    filename: function (req, file, cb) {
        cb(null, "input.txt");
    }
  })
 
  
var upload = multer({ storage: storage });
app.post("/upload_files", upload.single("file"), uploadFiles);


function uploadFiles(req,  res) {    
    res.json({ message: "Successfully uploaded files" });
}

app.post('/upload_parameters', (req, res) => {
    let data = '';
    req.on('data', chunk => {
      data += chunk;
    });
    req.on('end', () => {
        programType=JSON.parse(data).programType;
        loadOption=JSON.parse(data).loadOption;
        topsNum=JSON.parse(data).topsNum;
        topFrom=JSON.parse(data).topFrom;
        topTo=JSON.parse(data).topTo;
        console.log("Data parameters loaded");
        console.log(programType)
        res.end();
    });  
});
  

function excecute(response){
    const { exec } = require('child_process');
    exec('./main '+ topFrom+' ' + topTo + ' ' + loadOption + ' ' + topsNum + ' ' + programType, (err, stdout, stderr) => {
    if (err) {
        console.error(err)
    } else {
    console.log(`stdout: ${stdout}`);
    console.log(`stderr: ${stderr}`);
    response.json({ message: "Successfully run program" })
    }
    });
}

app.get('/download_data', (request, response) => {

    response.sendFile(__dirname+"/data.json")
    console.log("graph was successfully downloaded")
})

app.get('/download_res', (request, response) => {

    response.sendFile(__dirname+"/result.json")
    console.log("result was successfully downloaded")
})

function wait(ms){
    var start = new Date().getTime();
    var end = start;
    while(end < start + ms) {
      end = new Date().getTime();
   }
 }

app.get('/run', (request, response) => {
    excecute(response)
    // wait(7000)
    // response.json({ message: "Successfully run program" })
    
})