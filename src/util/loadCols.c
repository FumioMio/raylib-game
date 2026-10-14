#include "loadCols.h"
#include "../lib/json.h"
#include <assert.h>
#include <inttypes.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void LoadCols(const char *filepath, Cols *cols) {
  int rectCount = 0;

  char *filedata = LoadFileText(filepath);
  if (filedata == NULL) {
    TraceLog(LOG_ERROR, "gagal memuat file cols!");
    assert(false);
  }

  struct json_value_s *root = json_parse(filedata, strlen(filedata));
  if (root == NULL) {
    TraceLog(LOG_ERROR, "gagal mempharse json");
    UnloadFileText(filedata);
    assert(false);
  }

  struct json_object_s *root_object = json_value_as_object(root);

  struct json_object_element_s *root_element = root_object->start;
  while (root_element != NULL) {
    if (strcmp(root_element->name->string, "layers") == 0) {
      struct json_array_s *layer_array =
          json_value_as_array(root_element->value);

      struct json_array_element_s *layer_element = layer_array->start;
      while (layer_array != NULL) {
        struct json_object_s *layer_object =
            json_value_as_object(layer_element->value);

        const char *layer_name = "";
        struct json_array_s *objects_array = NULL;

        struct json_object_element_s *layer_prop = layer_object->start;
        while (layer_prop != NULL) {
          if (strcmp(layer_prop->name->string, "name") == 0) {
            layer_name = json_value_as_string(layer_prop->value)->string;
          }
          if (strcmp(layer_prop->name->string, "objects") == 0) {
            objects_array = json_value_as_array(layer_prop->value);
          }

          layer_prop = layer_prop->next;
        }

        if (strcmp(layer_name, "cols") == 0 && objects_array != NULL) {
          struct json_array_element_s *obj_element = objects_array->start;

          while (obj_element != NULL && rectCount < MAX_RECTANGLES) {
            struct json_object_s *obj =
                json_value_as_object(obj_element->value);

            float x = 0.0f, y = 0.0f, width = 0.0f, height = 0.0f;

            struct json_object_element_s *obj_prop = obj->start;
            while (obj_prop != NULL) {

              struct json_number_s *num_data =
                  json_value_as_number(obj_prop->value);

              if (num_data != NULL) {

                const char *prop_name = obj_prop->name->string;
                float val = strtof(num_data->number, NULL);

                if (strcmp(prop_name, "x") == 0) {
                  x = val;
                }
                if (strcmp(prop_name, "y") == 0) {
                  y = val;
                }
                if (strcmp(prop_name, "width") == 0) {
                  width = val;
                }
                if (strcmp(prop_name, "height") == 0) {
                  height = val;
                }
              }

              obj_prop = obj_prop->next;
            }

            cols->recs[rectCount] = (Rectangle){x, y, width, height};
            rectCount++;
            cols->actualSize = rectCount;

            obj_element = obj_element->next;
          }
          break;
        }
        layer_element = layer_element->next;
      }
    }
    root_element = root_element->next;
  }

  free((void *)root);

  UnloadFileText(filedata);
}
