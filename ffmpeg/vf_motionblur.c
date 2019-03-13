/**
 * @file
 * Motion blur filter.
 * 
 * Based on Codec debug viewer filter from
 * libavfilter/vf_codecview.c
 */

#include <libavfilter/avfilter.h>
#include <libavfilter/internal.h>
#include <libavutil/pixdesc.h>

typedef struct MotionBlurContext {
    int placeholder;
} MotionBlurContext;

static int query_formats(AVFilterContext *ctx)
{
    // anything with 8-bit luma in first plane should be working.
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_YUV444P,  AV_PIX_FMT_YUV422P,  AV_PIX_FMT_YUV420P,
        AV_PIX_FMT_YUV411P,  AV_PIX_FMT_YUV410P,
        AV_PIX_FMT_YUVJ444P, AV_PIX_FMT_YUVJ422P, AV_PIX_FMT_YUVJ420P,
        AV_PIX_FMT_YUV440P,  AV_PIX_FMT_YUVJ440P,
        AV_PIX_FMT_NONE
    };
    return ff_set_common_formats(ctx, ff_make_format_list(pix_fmts));
}

static int config_props(AVFilterLink *inlink)
{
    return 0;
}

static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out;
    if (av_frame_is_writable(in)) {
        out = in;
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, in);
    }

    if (out != in) {
        av_frame_copy(out, in);
        av_frame_free(&in);
    }

    return ff_filter_frame(outlink, out);
}

static const AVFilterPad motionblur_inputs[] = {
    {
        .name          = "default",
        .type          = AVMEDIA_TYPE_VIDEO,
        .filter_frame  = filter_frame,
        .config_props  = config_props
    },
    { NULL }
};

static const AVFilterPad motionblur_outputs[] = {
    {
        .name = "default",
        .type = AVMEDIA_TYPE_VIDEO,
    },
    { NULL }
};

AVFilter ff_vf_motionblur = {
    .name          = "motionblur",
    .description   = NULL_IF_CONFIG_SMALL("Apply motion blur filter."),
    .priv_size     = sizeof(MotionBlurContext),
    .query_formats = query_formats,
    .inputs        = motionblur_inputs,
    .outputs       = motionblur_outputs 
};