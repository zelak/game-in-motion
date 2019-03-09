/**
 * 
 */
#include "avinfo.h"
extern "C" {
#include <libavformat/avformat.h>
}

void avinfo::print_av_info(std::string video)
{
    // initialize libavformat and
    // register all the muxers,
    // demuxers and protocols.
    av_register_all();

    AVFormatContext * format_ctx = avformat_alloc_context();

    // open an input stream and
    // read the header.
    int rc = avformat_open_input(&format_ctx, video.c_str(), NULL, NULL);
    if (rc < 0) {
        // log::error("cannot open video file");
        return;
    }

    // read packets of a media file to
    // get stream information.
    rc = avformat_find_stream_info(format_ctx, NULL);
    if (rc < 0) {
        avformat_close_input(&format_ctx);
        // log::error("video info not found");
        return;
    }

    // print the media information
    av_dump_format(format_ctx, 0, video.c_str(), 0);

    avformat_close_input(&format_ctx);
}
