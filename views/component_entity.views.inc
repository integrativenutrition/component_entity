<?php

/**
 * @file
 */

/**
 * Implements hook_views_data_alter()
 */
function component_entity_views_data_alter(&$data) { 
  $data['component_entity']['link_component_entity'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the component_entity.'),
      'handler' => 'component_entity_handler_link_field',
    ),
  );
  $data['component_entity']['edit_component_entity'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the component_entity.'),
      'handler' => 'component_entity_handler_edit_link_field',
    ),
  );
  $data['component_entity']['delete_component_entity'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the component_entity.'),
      'handler' => 'component_entity_handler_delete_link_field',
    ),
  );
  $data['component_entity']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this component_entity.'),
      'handler' => 'component_entity_handler_component_entity_operations_field',
    ),
  );
}


/**
 * Implements hook_views_default_views().
 */
function component_entity_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'component_entities';
  $view->description = 'A list of all component_entities';
  $view->tag = 'component_entities';
  $view->base_table = 'component_entity';
  $view->human_name = 'ComponentEntities';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'ComponentEntities';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create any component_entity type';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'wcid' => 'wcid',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
  	'sortable' => 0,
  	'default_sort_order' => 'asc',
  	'align' => '',
  	'separator' => '',
    ),
    'wcid' => array(
  	'sortable' => 0,
  	'default_sort_order' => 'asc',
  	'align' => '',
  	'separator' => '',
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty ';
  $handler->display->display_options['empty']['area']['content'] = 'No component_entities have been created yet';
  /* Field: ComponentEntity: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'component_entity';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  /* Field: Field: Tags */
  $handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
  $handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tags']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
  /* Field: ComponentEntity: Sample Additional Field */
  $handler->display->display_options['fields']['field_sample_additional']['id'] = 'field_sample_additional';
  $handler->display->display_options['fields']['field_sample_additional']['table'] = 'field_data_field_sample_additional';
  $handler->display->display_options['fields']['field_sample_additional']['field'] = 'field_sample_additional';
  $handler->display->display_options['fields']['field_sample_additional']['element_label_colon'] = FALSE;
  /* Field: ComponentEntity: Componententity ID */
  $handler->display->display_options['fields']['wcid']['id'] = 'wcid';
  $handler->display->display_options['fields']['wcid']['table'] = 'component_entity';
  $handler->display->display_options['fields']['wcid']['field'] = 'wcid';
  $handler->display->display_options['fields']['wcid']['label'] = 'Select Entity';
  $handler->display->display_options['fields']['wcid']['element_label_colon'] = FALSE;
  /* Sort criterion: ComponentEntity: Name */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'component_entity';
  $handler->display->display_options['sorts']['name']['field'] = 'name';
  $handler->display->display_options['sorts']['name']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['name']['expose']['label'] = 'Name';
  /* Sort criterion: ComponentEntity: Sample Additional Field (field_sample_additional) */
  $handler->display->display_options['sorts']['field_sample_additional_value']['id'] = 'field_sample_additional_value';
  $handler->display->display_options['sorts']['field_sample_additional_value']['table'] = 'field_data_field_sample_additional';
  $handler->display->display_options['sorts']['field_sample_additional_value']['field'] = 'field_sample_additional_value';
  $handler->display->display_options['sorts']['field_sample_additional_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_sample_additional_value']['expose']['label'] = 'Sample Additional Field (field_sample_additional)';
  /* Sort criterion: Field: Tags (field_tags) */
  $handler->display->display_options['sorts']['field_tags_tid']['id'] = 'field_tags_tid';
  $handler->display->display_options['sorts']['field_tags_tid']['table'] = 'field_data_field_tags';
  $handler->display->display_options['sorts']['field_tags_tid']['field'] = 'field_tags_tid';
  $handler->display->display_options['sorts']['field_tags_tid']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_tags_tid']['expose']['label'] = 'Tags (field_tags)';
  /* Filter criterion: Field: Tags (field_tags) */
  $handler->display->display_options['filters']['field_tags_tid']['id'] = 'field_tags_tid';
  $handler->display->display_options['filters']['field_tags_tid']['table'] = 'field_data_field_tags';
  $handler->display->display_options['filters']['field_tags_tid']['field'] = 'field_tags_tid';
  $handler->display->display_options['filters']['field_tags_tid']['value'] = '';
  $handler->display->display_options['filters']['field_tags_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_tags_tid']['expose']['operator_id'] = 'field_tags_tid_op';
  $handler->display->display_options['filters']['field_tags_tid']['expose']['label'] = 'Tags (field_tags)';
  $handler->display->display_options['filters']['field_tags_tid']['expose']['operator'] = 'field_tags_tid_op';
  $handler->display->display_options['filters']['field_tags_tid']['expose']['identifier'] = 'field_tags_tid';
  $handler->display->display_options['filters']['field_tags_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_tags_tid']['vocabulary'] = 'tags';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'component_entities_admin_page');
  $handler->display->display_options['path'] = 'admin/content/component_entities/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['weight'] = '-10';
  $handler->display->display_options['tab_options']['type'] = 'tab';
  $handler->display->display_options['tab_options']['title'] = 'ComponentEntities';
  $handler->display->display_options['tab_options']['description'] = 'Manage component_entities';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  
  $views[] = $view;
  return $views;
}
