const fs=require('fs');
fs.copyFileSync("file1.txt","file2.txt");

const sh=require('superheroes');
const sv=require('supervillains');
console.log(sh.random() + " is in a deadly matchup with " + sv.random());
