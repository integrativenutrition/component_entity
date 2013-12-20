<?php
function component_entity_generate_entity($entity_info, $wcid = NULL) {
  if ($wcid) {
    $entity = entity_load_single($entity_info['bundle'], $wcid);
  }
  else {
    $entity = new ComponentEntity(array(
      'wcid' => NULL,
      'is_new' => 1,
      'bundle' => $entity_info['bundle'],
      'name' => isset($entity_info['name']) ? $entity_info['name'] : '',
      'created' => isset($entity_info['created']) && $entity_info['created'] ? $entity_info['created'] : time(),
      'changed' => isset($entity_info['changed']) && $entity_info['changed'] ? $entity_info['changed'] : time(),
      'language' => isset($entity_info['language']) ? $entity_info['language'] : 
        (language_default('language') == 'en' ? LANGUAGE_NONE : language_default('language')),
	  'type' => isset($entity_info['type']) ? $entity_info['type'] : '',
	  'form_key' => isset($entity_info['form_key']) ? $entity_info['form_key'] : '',
	  'value' => isset($entity_info['value']) ? $entity_info['value'] : '',
	  'extra' => isset($entity_info['extra']) ? serialize($entity_info['extra']) : array(),
	  'mandatory' => isset($entity_info['mandatory']) ? $entity_info['mandatory'] : 0,
	  'weight' => isset($entity_info['weight']) ? $entity_info['weight'] : 0,
    ));
    
  }
  component_entity_generate_fields($entity_info, $entity, 'component_entity', $entity->bundle);
  return entity_save($entity_info['bundle'], $entity);
}

function component_entity_generate_fields($entity_info, $object, $object_type, $bundle) {
  $field_types = field_info_field_types();
  $instances = field_info_instances($object_type, $bundle);
  foreach ($instances as $instance) {
    $field_name = $instance['field_name'];
    if (isset($entity_info[$field_name])) {
      $field = field_info_field($field_name);
      if (is_array($entity_info[$field_name]) && isset($entity_info[$field_name][0])) {
        $field_values = $entity_info[$field_name];
      }
      else {
        $field_values = array($entity_info[$field_name]);
      }

      $module = $field_types[$field['type']]['module'];
      $object_field = array();
      foreach ($field_values as $field_value) {
        $generator_function = 'component_entity_' . $module . '_generate';
        if (function_exists($generator_function)) {
          $result = $generator_function($field_value, $object, $field, $instance, $bundle);
          if ($result) {
            $object_field[] = $result;
          }
        }
      }
      $object->{$field['field_name']} = array(
        $object->language => $object_field,
        LANGUAGE_NONE => $object_field,
      );
    }
  }
}
