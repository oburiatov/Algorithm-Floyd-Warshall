const express = require('express');
const app = express()
const cors = require('cors');
app.use(cors());
app.use(express.static('public'));

const PORT = 3001
app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`)
})

const multer = require("multer");

var storage = multer.diskStorage({
    destination: function (req, file, cb) {
      cb(null, './uploads/.')
    },
    filename: function (req, file, cb) {
        const {originalname} = file;
        cb(null, originalname);
    }
  })
 
  
var upload = multer({ storage: storage });
app.post("/upload_files", upload.single("file"), uploadFiles);

function uploadFiles(req,  res) {    
    console.log(req.body);
    console.log(req.file);
    res.json({ message: "Successfully uploaded files" });
}

function hello(){
    const { exec } = require('child_process');
    exec('./main 1 2 file hello', (err, stdout, stderr) => {
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

