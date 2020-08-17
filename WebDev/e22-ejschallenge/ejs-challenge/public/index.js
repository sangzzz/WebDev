let para = $('p.post');
for (let i = 0; i < para.length; i++) {
  para[i].text(para.text().substring(0, 100) + "... ");
}
