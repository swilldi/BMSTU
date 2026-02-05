#include "request.h"

error_code complete_request(request_t request)
{
    error_code rc = OK;
    static model_t model = model_init();
    FILE *f;

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
            f = fopen(request.file_name, "r");
            if (!f)
            {
                rc = FILE_OPEN_ERR;
                break;
            }
            rc = model_read_from_file(f, model);
            break;
        case SAVE:
            f = fopen(request.file_name, "w");
            if (!f)
            {
                rc = FILE_OPEN_ERR;
                break;
            }
            rc = model_write_to_file(f, model);
            break;

        case EXIT:
            model_free(model);
            break;
        default:
            break;
    }

    return rc;
}
