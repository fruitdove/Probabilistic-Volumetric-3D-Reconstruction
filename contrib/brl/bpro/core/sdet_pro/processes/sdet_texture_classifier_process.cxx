// This is brl/bpro/core/sdet_pro/processes/sdet_texture_classifier_process.cxx
//:
// \file

#include <bprb/bprb_func_process.h>
#include <bprb/bprb_parameters.h>
#include <brdb/brdb_value.h>
#include <sdet/sdet_texture_classifier.h>
#include <sdet/sdet_texture_classifier_params.h>
#include <vil/vil_image_view.h>
//: initialize input and output types
bool sdet_texture_classifier_process_cons(bprb_func_process& pro)
{
  // process takes 3 inputs:
  vcl_vector<vcl_string> input_types;
  input_types.push_back("vcl_string"); //texton dictionary
  input_types.push_back("vcl_string"); //input image path
  input_types.push_back("unsigned");   //texture block size
  if (!pro.set_input_types(input_types))
    return false;

  // process has 1 output:
  // output[0]: output texture color image
  vcl_vector<vcl_string> output_types;
  output_types.push_back("vil_image_view_base_sptr");
  return pro.set_output_types(output_types);
}

//: generates the edge map
bool sdet_texture_classifier_process(bprb_func_process& pro)
{
  if (!pro.verify_inputs())
  {
    vcl_cout << pro.name() << "texture classifier process inputs are not valid "<< vcl_endl;
    return false;
  }
  // get inputs
  vcl_string texton_dict_path = pro.get_input<vcl_string>(0);
  vcl_string image_path = pro.get_input<vcl_string>(1);
  unsigned block_size = pro.get_input<unsigned>(2);
  sdet_texture_classifier_params tcp;
  tcp.signed_response_ = true;
  tcp.mag_ = false;
  tcp.block_size_ = block_size;
  sdet_texture_classifier tc(tcp);
  tc.load_dictionary(texton_dict_path);
  vil_image_view<float> class_img =
    tc.classify_image_blocks_qual(image_path);
  // return the output image
    vil_image_view_base_sptr img_ptr = new vil_image_view<float>(class_img);
  pro.set_output_val<vil_image_view_base_sptr>(0, img_ptr);
  return true;
}