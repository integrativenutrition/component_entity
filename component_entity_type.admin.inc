<?php

/**
 * @file
 * ComponentEntity type editing UI.
 */

/**
 * UI controller.
 */
class ComponentEntityTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
		$items[$this->path]['description'] = 'Manage component_entity entity types, including adding
		and removing fields and the display of fields.';
    return $items;
  }
}

/**
 * Generates the component_entity type editing form.
 */
function component_entity_type_form($form, &$form_state, $component_entity_type, $op = 'edit') {

  if ($op == 'clone') {
    $component_entity_type->label .= ' (cloned)';
    $component_entity_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $component_entity_type->label,
    '#description' => t('The human-readable name of this component_entity type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($component_entity_type->type) ? $component_entity_type->type : '',
    '#maxlength' => 32,
//    '#disabled' => $component_entity_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'component_entity_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this component_entity type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['data']['#tree'] = TRUE;

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save component_entity type'),
    '#weight' => 40,
  );

  //Locking not supported yet
  /*if (!$component_entity_type->isLocked() && $op != 'add') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete component_entity type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('component_entity_type_form_submit_delete')
    );
  }*/
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function component_entity_type_form_submit(&$form, &$form_state) {
  $component_entity_type = entity_ui_form_submit_build_entity($form, $form_state);
  $component_entity_type->save();
  $form_state['redirect'] = 'admin/structure/component_entity_types';
}

/**
 * Form API submit callback for the delete button.
 */
function component_entity_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/component_entity_types/manage/' . $form_state['component_entity_type']->type . '/delete';
}
