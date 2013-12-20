<?php
function component_entity_text_generate($field_value, $object, $field, $instance, $bundle) {
  $object_field = array();
  $object_field['format'] = 'full_html';
  if ($instance['widget']['type'] != 'text_textfield') {
    $object_field['value'] = is_array($field_value) && isset($field_value['value']) ? $field_value['value'] : $field_value;
    if ($instance['widget']['type'] == 'text_textarea_with_summary') {
      $object_field['summary'] = is_array($field_value) && isset($field_value['summary']) ? $field_value['summary'] : "";
      if(isset($field_value['format'])) {
      	$object_field['format'] = $field_value['format'];
      }
    }
  }
  else {
  	$object_field['value'] = $field_value;
  }
  return $object_field;
}

function component_entity_image_generate($url, $object, $field, $instance, $bundle) {
  $info = pathinfo($url);
  $filename = isset($info['filename']) ? $info['filename'] : "";
  $extension = isset($info['extension']) ? $info['extension'] : 'png';

  $object_field = array();
  $path = component_entity_download_image($url);
  if ($path) {
    $source = new stdClass();
    $source->uri = $path;
    $source->uid = 1;
    $source->filemime = 'image/' . pathinfo($path, PATHINFO_EXTENSION);
    $destination_dir = $field['settings']['uri_scheme'] . '://' . $instance['settings']['file_directory'];
    file_prepare_directory($destination_dir, FILE_CREATE_DIRECTORY);
    $counter = 0;
    $destination = $destination_dir . '/' . $filename . "." . $extension;
    $realpath = drupal_realpath($destination); 
    while (file_exists($realpath)) {
      $counter ++;
      $destination = $destination_dir . '/' . $filename . ($counter ? "_" . $counter : "") . "." . $extension;
      $realpath = drupal_realpath($destination); 
    }
    $source->filename = $filename . ($counter ? "_" . $counter : "") . "." . $extension;
    $file = file_move($source, $destination, FILE_CREATE_DIRECTORY);
  }
  else {
    return NULL;
  }

  $object_field['fid'] = $file->fid;
  $object_field['alt'] = '';
  $object_field['title'] = '';
  return $object_field;  
}

function component_entity_download_image($input_path) {
  $info = pathinfo($input_path);
  $extension = isset($info['extension']) ? $info['extension'] : 'png';
  $tmp_file = drupal_tempnam('temporary://', 'imagefield_');
  if ($tmp_file) {
    $content = file_get_contents(drupal_get_path('module', 'component_entity') . "/" . $input_path);
    $destination = $tmp_file . '.' . $extension;
    $path = file_unmanaged_move($tmp_file, $destination, FILE_CREATE_DIRECTORY);
    file_put_contents(drupal_realpath($path), $content);
  }
  return $destination;
}

function component_entity_taxonomy_generate($field_value, $object, $field, $instance, $bundle) {
  $str = $field_value;
  $field_value = trim($field_value);
  $machine_name = $field['settings']['allowed_values'][0]['vocabulary'];
  $vocabulary = taxonomy_vocabulary_machine_name_load($machine_name);
  $query = db_select('taxonomy_term_data', 't');
  $tid = $query
    ->fields('t', array('tid'))
    ->condition('t.vid', $vocabulary->vid, '=')
    ->condition('t.name', $field_value)
    ->range(0, 1)
    ->execute()
    ->fetchField();
  if ($tid === FALSE) {
    $term_info = array(
      'name' => $field_value,
      'description' => $field_value,
      'vid' => $vocabulary->vid,
    );
    $term_object = (object) $term_info;
    taxonomy_term_save($term_object);  	
  }
  $query = db_select('taxonomy_term_data', 't');
  $tid = $query
    ->fields('t', array('tid'))
    ->condition('t.vid', $vocabulary->vid, '=')
    ->condition('t.name', $field_value)
    ->range(0, 1)
    ->execute()
    ->fetchField();
  $object_field = array();
  $object_field['tid'] = (int) $tid;
  return $object_field;
}

function component_entity_file_generate($field_value, $object, $field, $instance, $bundle) {
  return array("");
}

function component_entity_number_generate($field_value, $object, $field, $instance, $bundle) {
  return array(is_numeric($field_value) ? $field_value : 0);
}

function component_entity_date_generate($field_value, $object, $field, $instance, $bundle) {
  $time = strtotime($field_value);
  $str = date('Y-m-d H:i:s', $time); 
  return array('value' => $str);
}

function component_entity_link_generate($field_value, $object, $field, $instance, $bundle){
  $object_field = array();
  $object_field['url'] = $field_value['url'];
  $object_field['title'] = $field_value['title'];
  $object_field['attributes'] = array();
  return $object_field;
}

function component_entity_money_generate($field_value, $object, $field, $instance, $bundle){
  $object_field = array();
  $object_field['amount'] = $field_value;
  $object_field['currency'] = 'EUR';
  return $object_field;
}

function component_entity_youtube_generate($field_value, $object, $field, $instance, $bundle){
  $object_field = array();
  $object_field['input'] = $field_value;
  $data = explode('=', $field_value);
  $object_field['video_id'] = $data[count($data)-1];
  return $object_field;
}

