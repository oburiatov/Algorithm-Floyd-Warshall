const express = require('express');
const app = express()
const cors = require('cors');
app.use(cors());
app.use(express.static('public'));

var fs = require('fs');
var https = require('https');
var privateKey  = fs.readFileSync('/app/ssl/devopseek.key', 'utf8');
var certificate = fs.readFileSync('/app/ssl/devopseek.crt', 'utf8');
var credentials = {key: privateKey, cert: certificate};
var httpsServer = https.createServer(credentials, app);


const PORT = 30501
httpsServer.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`)
});

let loadOption = "gen";
let topFrom = "NULL";
let topTo = "NULL";
let topsNum = "NULL";

// app.listen(PORT, () => {
//     console.log(`Server running on port ${PORT}`)
// })

const multer = require("multer");

var storage = multer.diskStorage({
    destination: function (req, file, cb) {
      cb(null, '.')
    },
    filename: function (req, file, cb) {
        cb(null, "data.txt");
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
        loadOption=JSON.parse(data).loadOption;
        topsNum=JSON.parse(data).topsNum;
        topFrom=JSON.parse(data).topFrom;
        topTo=JSON.parse(data).topTo;
        console.log("Data parameters loaded");
        res.end();
    });  
});
  

function hello(){
    const { exec } = require('child_process');
    exec('./main '+ topFrom+' ' + topTo + ' ' + loadOption + ' ' + topsNum, (err, stdout, stderr) => {
    if (err) {
        //some err occurred
        console.error(err)
    } else {
    console.log(`stdout: ${stdout}`);
    console.log(`stderr: ${stderr}`);
    }
    });
}

app.get('/result', (request, response) => {
    hello()
    response.send()
})

