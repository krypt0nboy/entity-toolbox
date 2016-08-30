<?php

/**
 * Build and attaches a field ui form to add heritage settings.
 *
 * @param array $form
 *   The form to attach the setting to.
 * @param array $form_state
 *   The form state.
 */
function field_heritage_settings_attach(&$form, &$form_state) {
  if (!empty($form['instance']['settings']['toolbox']['inherit'])) {
    $setting                   = &$form['instance']['settings']['toolbox']['inherit'];
    $setting['#default_value'] = !empty($form['#instance']['settings']['toolbox']['inherit']) ? $form['#instance']['settings']['toolbox']['inherit'] : '';
  }
  else {
    $form['instance']['settings']['toolbox']['inherit'] = array(
      '#type'          => 'checkbox',
      '#title'         => t('Children inherit'),
      '#description'   => t('Should the children inherit the value ?'),
      '#default_value' => '',
    );
  }
}

/**
 * Attach an entity properties to a form.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param array          $form
 *   The form, passed by reference.
 * @param array          $form_state
 *   The form_state, passed by reference.
 * @param string         $langcode
 *   The language code.
 * @param string[]       $options
 *   The property fields options.
 */
function properties_attach_form($entity_type, $entity, &$form, &$form_state, $langcode = NULL, $options = array()) {
  foreach ($entity->toolboxInfo()['properties'] as $name => $property) {
    property_attach_form($entity_type, $entity, $name, $form, $form_state, $langcode, $options);
  }
}

/**
 * Attach a property to an entity form.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param array          $form
 *   The form, passed by reference.
 * @param array          $form_state
 *   The form_state, passed by reference.
 * @param string         $langcode
 *   The language code.
 * @param array          $options
 *   The property fields options.
 */
function property_attach_form($entity_type, $entity, $name, &$form, &$form_state, $langcode = NULL, $options = array()) {
  $toolbox_info = $entity->toolboxInfo();
  $property     = $toolbox_info['properties'][$name];
  //Check if the property is set to be exposed for this form.
  if (!empty($property['expose']['forms'][entity_form_type($form['form_id'])])) {
    $function = entity_toolbox_is_property_multi_value($entity_type, $name) ? 'property_multi_attach_form' : 'property_single_attach_form';
    $function($entity_type, $entity, $name, $form, $form_state, $langcode, $options);
    foreach (module_implements('property_attach_form') as $module) {
      $hook = $module . '_property_attach_form';
      $hook($entity_type, $entity, $name, $form, $form_state, $langcode, $options);
    }
  }
}

/**
 * Attach a property to an entity form.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param array          $form
 *   The form, passed by reference.
 * @param array          $form_state
 *   The form_state, passed by reference.
 * @param string         $langcode
 *   The language code.
 * @param array          $options
 *   The property fields options.
 */
function property_single_attach_form($entity_type, $entity, $name, &$form, &$form_state, $langcode = NULL, $options = array()) {
  $form[$name] = property_element_build($entity_type, $entity, $name, $form['form_id'], NULL, $options);
}

/**
 * Attach a property to an entity form.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param array          $form
 *   The form, passed by reference.
 * @param array          $form_state
 *   The form_state, passed by reference.
 * @param string         $langcode
 *   The language code.
 * @param array          $options
 *   The property fields options.
 */
function property_multi_attach_form($entity_type, $entity, $name, &$form, &$form_state, $langcode = NULL, $options = array()) {
  $form[$name] = property_element_build($entity_type, $entity, $name, $form['form_id'], NULL, $options);
}

/**
 * Builds a property field to be used in an entity form.
 *
 * @param string         $entity_type
 *   The entity type for which the field is built.
 * @param \EntityToolbox $entity
 *   The entity for which the field is built.
 * @param string         $name
 *   The property name.
 * @param string         $form_id
 *   The form ID.
 * @param null|string    $widget
 *   The widget type, or NULL to use the property type default widget.
 * @param array          $options
 *   The options, such as js_enabled, etc...
 *
 * @return array
 *
 * @see hook_property_element_alter().
 *
 * @todo Add hook_property_element_build().
 * @todo handle multiple properties with add_more_wrapper.
 */
function property_element_build($entity_type, $entity, $name, $form_id, $widget = NULL, $options = array()) {
  $toolbox_info = $entity->toolboxInfo();
  $property     = $toolbox_info['properties'][$name];
  $element      = array(
    '#type'          => toolbox_widget2form_field_type($widget, $property['multiple']),
    '#title'         => $property['label'],
    '#description'   => !empty($property['description']) ? $property['description'] : '',
    '#default_value' => entity_property_default($entity_type, $entity, $name),
    '#required'      => $property['required'][entity_form_type($form_id)],
  );

  //Let other modules alter the element.
  _property_element_alter($element, $entity_type, $entity, $name, $form_id, $widget, $options);

  return $element;
}

/**
 * Builds the ajax component of an entity field.
 *
 * @param string         $entity_type
 *   The entity type for which the field is built.
 * @param \EntityToolbox $entity
 *   The entity for which the field is built.
 * @param string         $name
 *   The property name.
 * @param string         $form_id
 *   The form ID.
 * @param null|string    $widget
 *   The widget type, or NULL to use the property type default widget.
 * @param array          $options
 *   The entity form options, such as js_enabled, etc...
 *
 * @return array
 */
function property_element_ajax_build($entity_type, $entity, $name, $form_id, $widget = NULL, $options = array()) {
  $ajax = array(
    'callback' => 'property_ajax_process',
    //@todo evaluate the type of property, widget to define which event to set
    'event'    => '',
    'effect'   => !empty($options['effect']) ? $options['effect'] : 'fade',
    'method'   => 'replace',
    //@todo add property_element_get_ajax_wrapper() function.
    'wrapper'  => '',
    //@todo add ajax progress
  );

  return $ajax;
}

/**
 * Implements hook_property_element_alter().
 */
function entity_toolbox_property_element_alter($entity_type, $entity, $name, $form_id, &$element, $widget = NULL, $options = array()) {
  /**
   * Check if the property is to be inherited from one or more parents
   */
  if (in_array($name, array_keys(entity_toolbox_get_inherited_properties($entity_type)))) {
    $element['#ajax'] = property_element_ajax_build($entity_type, $entity, $name, $form_id, $widget, $options);
  }
}

/**
 * Validates a properties attached to a form.
 *
 * @param string $entity_type
 *   The entity type.
 * @param object $entity
 *   The entity to validate.
 * @param array  $form
 *   The entity form.
 * @param array  $form_state
 *   The form state, passed by reference.
 * @param array  $options
 *   The form options.
 */
function properties_attach_form_validate($entity_type, $entity, &$form, &$form_state, $options = array()) {
  foreach (entity_toolbox_get_info($entity_type)['properties'] as $name => $property) {
    property_attach_form_validate($entity_type, $entity, $form, $form_state, $options);
  }
}

/**
 * Validates a property attached to a form.
 *
 * @param string $entity_type
 *   The entity type.
 * @param object $entity
 *   The entity to validate.
 * @param string $property
 *   The property to validate.
 * @param array  $form
 *   The entity form.
 * @param array  $form_state
 *   The form state, passed by reference.
 * @param array  $options
 *   The form options.
 */
function property_attach_form_validate($entity_type, $entity, $property, $form, &$form_state, $options = array()) {
  //@todo add entity_property_validate().
  //@todo add _property_attach_form_validate()
}

/**
 * Submits properties attached to a form.
 *
 * @param string $entity_type
 *   The entity type.
 * @param object $entity
 *   The entity to validate.
 * @param array  $form
 *   The entity form.
 * @param array  $form_state entity_toolbox_ui_controller($entity_type)->entityEditFormSubmit($form, $form_state);
 *   The form state, passed by reference.
 * @param array  $options
 *   The form options.
 */
function properties_attach_form_submit($entity_type, $entity, &$form, &$form_state, $options = array()) {
  foreach (entity_toolbox_get_info($entity_type)['properties'] as $name => $property) {
    property_attach_form_submit($entity_type, $entity, $form, $form_state, $options);
  }
}

/**
 * Submits a property attached to a form.
 *
 * @param string $entity_type
 *   The entity type.
 * @param object $entity
 *   The entity to validate.
 * @param string $property
 *   The property to submit.
 * @param array  $form
 *   The entity form.
 * @param array  $form_state
 *   The form state, passed by reference.
 * @param array  $options
 *   The form options.
 */
function property_attach_form_submit($entity_type, $entity, $property, &$form, &$form_state, $options = array()) {
  //@todo _property_attach_form_submit()
}

/**
 * Process a property field returned in an AJAX query for evaluation.
 *
 * @param array  $form
 *   The entity form.
 * @param array  $form_state
 *   The entity form state.
 * @param string $name
 *   The property name.
 */
function property_ajax_process($form, &$form_state, $name) {
  //@todo add hook_property_ajax_process().
}

/**
 * Process an entity field returned in an AJAX query for evaluation.
 *
 * @param array  $form
 *   The entity form.
 * @param array  $form_state
 *   The entity form state.
 * @param string $name
 *   The field name.
 */
function field_ajax_process($form, &$form_state, $name) {
  //@todo add hook_field_ajax_process().
}

/**
 * Extract property values from an entity form.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param array          $items
 *   The property values, passed by reference.
 * @param null|string    $langcode
 *   The langcode, defaults to NULL.
 * @param array          $form
 *   The entity form.
 * @param array          $form_state
 *   The form state, passed by reference.
 */
function property_default_extract_form_values($entity_type, $entity, $name, &$items, $langcode = NULL, $form, &$form_state) {}