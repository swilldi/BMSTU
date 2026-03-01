#include "request.h"
#include "model.h"


error_code complete_request(const request_t &request)
{
    error_code rc = OK;
    static model_t model = model_init();

    switch (request.action)
    {
        case DRAW:
            rc = model_draw(request.scene, model);
            break;

        case MOVE:
            rc = model_move(model, request.move);
            break;
        case ROTATE:
            rc = model_rotate(model, request.rotate);
            break;
        case SCALE:
            rc = model_scale(model, request.scale);
            break;

        case LOAD:
            rc = model_load(model, request.file_name);
            break;
        case SAVE:
            rc = model_save(request.file_name, model);
            break;

        case EXIT:
            model_free(model);
            break;
        default:
            rc = ACTION_INVALID;
            break;
    }

    return rc;
}
