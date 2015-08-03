module.exports = {

    website: {
        assets: "./assets",
        css: [
            "player.css"
        ]
    },

    blocks: {
        youtube: {
            process: function(blk) {

                var vid = blk.body.trim();

                if(vid.length == 0) {
                  console.log('\n[gitbook-plugin-youtubex]('+this.ctx.file.path+') Error: video ID is empty.');
                  return null;
                }

                if(vid.indexOf("'") > -1 || vid.indexOf('"') > -1) {
                  console.log('\n[gitbook-plugin-youtubex]('+this.ctx.file.path+') Error: input ID contains invalid character(s).');
                  return null;
                }

                if(this.generator === 'website')
                    return '<div class="youtubex-container"><iframe src="https://www.youtube.com/embed/' + vid + '" allowfullscreen width="100%" height="100%"></iframe><div>';
                else
                    return '<blockquote><b>Embedded Video:<b>&nbsp;<a href="https://www.youtube.com/watch?v=' + vid + '">' + 'https://www.youtube.com/watch?v=' + vid + '</a></blockquote>';
            }
        }
    }
};
