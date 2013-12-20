<?php

/**
 * @file
 */

/**
 * Form callback wrapper: create or edit a component_entity.
 *
 * @param $component_entity
 *   The component_entity object being edited by this form.
 *
 * @see component_entity_edit_form()
 */
function component_entity_form_wrapper($component_entity) {
  component_entity_set_breadcrumb();
  return drupal_get_form('component_entity_edit_form', $component_entity);
}


/**
 * Form callback wrapper: delete a component_entity.
 *
 * @param $component_entity
 *   The component_entity object being edited by this form.
 *
 * @see component_entity_edit_form()
 */
function component_entity_delete_form_wrapper($component_entity) {
  return drupal_get_form('component_entity_delete_form', $component_entity);
}


/**
 * Form callback: create or edit a component_entity.
 *
 * @param $component_entity
 *   The component_entity object to edit or for a create form an empty component_entity object
 *     with only a component_entity type defined.
 */
function component_entity_edit_form($form, &$form_state, $component_entity) {
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('ComponentEntity Name'),
    '#default_value' => isset($component_entity->name) ? $component_entity->name : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );
  
  $form['data']['#tree'] = TRUE;

  $form_state['component_entity'] = $component_entity;
  field_attach_form('component_entity', $component_entity, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save component_entity'),
    '#submit' => $submit + array('component_entity_edit_form_submit'),
  );
  
  if (!empty($component_entity->name)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete component_entity'),
      '#suffix' => l(t('Cancel'), 'admin/content/component_entities'),
      '#submit' => $submit + array('component_entity_form_submit_delete'),
      '#weight' => 45,
    );
  }

  $form['#validate'][] = 'component_entity_edit_form_validate';
  return $form;
}


/**
 * Form API validate callback for the component_entity form
 */
function component_entity_edit_form_validate(&$form, &$form_state) {
  $component_entity = $form_state['component_entity'];
  
  // Notify field widgets to validate their data.
  field_attach_form_validate('component_entity', $component_entity, $form, $form_state);
}


/**
 * Form API submit callback for the component_entity form.
 * 
 * @todo remove hard-coded link
 */
function component_entity_edit_form_submit(&$form, &$form_state) {
  
  $component_entity = entity_ui_controller('component_entity')->entityFormSubmitBuildEntity($form, $form_state);
  
  if ($component_entity->is_new = isset($component_entity->is_new) ? $component_entity->is_new : 0){
    $component_entity->created = time();
  }

  $component_entity->changed = time();
  
  $component_entity->save();
  $form_state['redirect'] = 'admin/content/component_entities';
}

/**
 * Form API submit callback for the delete button.
 * 
 * @todo Remove hard-coded path
 */
function component_entity_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/component_entities/component_entity/' . $form_state['component_entity']->wcid . '/delete';
}


/**
 * Form callback: confirmation form for deleting a component_entity.
 *
 * @param $component_entity
 *   The component_entity to delete
 *
 * @see confirm_form()
 */
function component_entity_delete_form($form, &$form_state, $component_entity) {
  $form_state['component_entity'] = $component_entity;

  $form['#submit'][] = 'component_entity_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete component_entity %name?', array('%name' => $component_entity->name)),
    'admin/content/component_entities/component_entity',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );
  
  return $form;
}

/**
 * Submit callback for component_entity_delete_form
 */
function component_entity_delete_form_submit($form, &$form_state) {
  $component_entity = $form_state['component_entity'];

  component_entity_delete($component_entity);

  drupal_set_message(t('The component_entity %name has been deleted.', array('%name' => $component_entity->name)));
  watchdog('component_entity', 'Deleted component_entity %name.', array('%name' => $component_entity->name));

  $form_state['redirect'] = 'admin/content/component_entities';
}



/**
 * Page to add ComponentEntity Entities.
 *
 * @todo Pass this through a proper theme function
 */
function component_entity_add_page() {
  $controller = entity_ui_controller('component_entity');
  return $controller->addPage();
}


/**
 * Displays the list of available component_entity types for component_entity creation.
 *
 * @ingroup themeable
 */
function theme_component_entity_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="component_entity-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer component_entity types')) {
      $output = '<p>' . t('ComponentEntity Entities cannot be added because you have not created any component_entity types yet. Go to the <a href="@create-component_entity-type">component_entity type creation page</a> to add a new component_entity type.', array('@create-component_entity-type' => url('admin/structure/component_entity_types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No component_entity types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}

/**
 * Sets the breadcrumb for administrative component_entity pages.
 */
function component_entity_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('ComponentEntities'), 'admin/content/component_entities'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
