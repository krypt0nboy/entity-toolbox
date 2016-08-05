<?php

/**
 * @file
 *
 * This file contains validation and translation functions required by entity_toolbox.
 */

/**
 * Returns the type of an entity.
 *
 * @param \Entity $entity
 *  The entity to get the type from.
 *
 * @return string|null
 *  Returns NULL if method 'entityType' does not exist for the entity.
 */
function entity_type($entity) {
  return method_exists($entity, 'entityType') ? $entity->entityType() : NULL;
}

/**
 * Returns the bundle of an entity.
 *
 * @param \Entity $entity
 *  The entity.
 *
 * @return string
 */
function entity_bundle($entity) {
  return $entity->bundle();
}

/**
 * Returns the author of the entity.
 *
 * @param \Entity|\EntityToolbox $entity
 *   The entity.
 *
 * @return Entity
 */
function entity_author($entity) {
  //@todo add entity_type_is_entity_toolbox()
  $entity_type = $entity->entityType();
  if (in_array($entity_type, entity_toolbox_entity_get_info())) {
	$controller = entity_toolbox_controller($entity_type);

	return $controller->author($entity);
  }
  else {
	return user_load($entity->uid);
  }
}

/**
 * Returns the entity author uid.
 *
 * @param \Entity|\EntityToolbox $entity
 *   The entity.
 *
 * @return int
 */
function entity_author_id($entity) {
//@todo add entity_type_is_entity_toolbox()
  $entity_type = $entity->entityType();
  if (in_array($entity_type, entity_toolbox_entity_get_info())) {
	$controller = entity_toolbox_controller($entity_type);

	return $controller->authorUid($entity);
  }
  else {
	return $entity->uid;
  }
}

/**
 * Returns an entity wrapper object.
 * No need to specify the entity type.
 *
 * @param \Entity $entity
 *   The entity to get the wrapper for.
 *
 * @return \EntityMetadataWrapper
 */
function entity_wrapper($entity) {
  return entity_metadata_wrapper(entity_type($entity), $entity);
}

/**
 * Returns every property type declared and allowed by entity_toolbox.
 *
 * @return array
 */
function toolbox_property_types() {
  return array_keys(entity_toolbox_property_type_get_info());
}

/**
 * Defaults views handlers for a numeric property.
 * References that are not multi value should use those default handlers as well.
 *
 * @return array
 */
function toolbox_numeric_property_default_views_handlers() {
  return array(
	'field'    => array(
	  'handler'        => 'views_handler_field_numeric',
	  'click sortable' => TRUE
	),
	'filter'   => array('handler' => 'views_handler_field_numeric'),
	'sort'     => array('handler' => 'views_handler_field_numeric'),
	'argument' => array('handler' => 'views_handler_field_numeric'),
  );
}

/**
 * Defaults views handlers for a string property.
 *
 * @return array
 */
function toolbox_string_property_default_views_handlers() {
  return array(
	'field'    => array(
	  'handler'        => 'views_handler_field',
	  'click sortable' => TRUE
	),
	'filter'   => array('handler' => 'views_handler_filter_string'),
	'sort'     => array('handler' => 'views_handler_sort'),
	'argument' => array('handler' => 'views_handler_argument_string'),
  );
}

/**
 * Default views handlers for a boolean property.
 *
 * @return array
 */
function toolbox_boolean_property_default_views_handlers() {
  return array(
	'field'    => array(
	  'handler'        => 'views_handler_field_boolean',
	  'click sortable' => TRUE
	),
	'filter'   => array(
	  'handler'   => 'views_handler_field_boolean_operator',
	  'type'      => 'yes-no',
	  'use equal' => TRUE,
	),
	'sort'     => array('handler' => 'views_handler_sort'),
	'argument' => array('handler' => 'views_handler_argument_string'),
  );
}

/**
 * Default views handlers for a date property.
 * Can be used for any date related property.
 *
 * @return array
 */
function toolbox_date_property_default_views_handlers() {
  return array(
	'field'  => array(
	  'handler'        => 'views_handler_field_date',
	  'click sortable' => TRUE
	),
	'filter' => array('handler' => 'views_handler_filter_date'),
	'sort'   => array('handler' => 'views_handler_sort_date'),
  );
}

/**
 * Default views handlers for a serialized property.
 *
 * @return array
 */
function toolbox_serialized_property_default_views_handlers() {
  return array('field' => array('handler' => 'views_handler_field_serialized'));
}

/**
 * Default views handlers for an entity property.
 *
 * @return array
 */
function toolbox_entity_property_default_views_handlers() {
  return array('field' => array('handler' => 'views_handler_field_entity'));
}

/**
 * Returns the default entity_toolbox widget of a property type.
 *
 * @param string $type
 *   The property type.
 *
 * @return null|string
 */
function toolbox_property_default_widget($type) {
  $info = entity_toolbox_property_type_get_info($type);

  return !empty($info['default_widget']) ? $info['default_widget'] : NULL;
}

/**
 * Translate an entity_toolbox property type to a drupal property type.
 *
 * @param string $type
 *   The toolbox property type.
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 * @param bool   $multiple
 *   A boolean to indicate if the property is multiple.
 *
 * @return string
 */
function toolbox_property2drupal_property($type, $entity_type = NULL, $name = NULL, $multiple = FALSE) {
  $info = entity_toolbox_property_type_get_info($type);
  if (!empty($info['drupal_property_callback'])) {
	$callback = !empty($info['drupal_property_callback']) ? $info['drupal_property_callback'] : '';

	return isset($callback) ? $callback($entity_type, $name) : '';
  }
  else {
	return !empty($info['drupal_property']) ? $info['drupal_property'] : '';
  }
}

/**
 * Returns a list property type for drupal system when processing a multi value property.
 *
 * @param $type
 *   The drupal property type.
 *
 * @return string
 */
function toolbox_multiple2drupal_multiple($type) {
  return "list<$type>";
}

/**
 * Returns a drupal property type from a toolbox reference.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return string
 */
function toolbox_reference_type($entity_type, $name) {
  $property = entity_toolbox_entity_get_info($entity_type)['properties'][$name];

  return $property['reference'];
}

/**
 * Returns the processed name for an entity schema.
 *
 * @param string $type
 *   The schema type.
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function toolbox_schema_type_process_name($type, $entity_type) {
  $schema_info = entity_toolbox_schema_type_get_info($type);
  $string      = $schema_info['name'];
  $wildcards   = string_extract_wildcards($schema_info['name']);
  //add variables

  $variables = array();

  return string_replace_tokens($string, $wildcards, $variables);
}

/**
 * Returns an entity type class, processed by entity toolbox.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function toolbox_entity_get_class($entity_type) {
  $classes = &drupal_static(__FUNCTION__, array());
  if (!isset($classes[$entity_type])) {
	$toolbox_info          = entity_toolbox_entity_get_info($entity_type);
	$classes[$entity_type] = $toolbox_info['classes']['entities']['entity'];
  }

  return $classes[$entity_type];
}

/**
 * Returns an entity type controller class, processed by entity toolbox.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function toolbox_entity_get_controller_class($entity_type) {
  $classes = &drupal_static(__FUNCTION__, array());
  if (!isset($classes[$entity_type])) {
	$toolbox_info          = entity_toolbox_entity_get_info($entity_type);
	$classes[$entity_type] = $toolbox_info['classes']['controllers']['controller'];
  }

  return $classes[$entity_type];
}

/**
 * Returns an entity type ui controller class, processed by entity toolbox.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function toolbox_entity_get_ui_controller_class($entity_type) {
  $classes = &drupal_static(__FUNCTION__, array());
  if (!isset($classes[$entity_type])) {
	$toolbox_info          = entity_toolbox_entity_get_info($entity_type);
	$classes[$entity_type] = $toolbox_info['classes']['controllers']['ui'];
  }

  return $classes[$entity_type];
}

/**
 * Returns an entity type inline entity form controller class, processed by entity toolbox.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function toolbox_entity_get_inline_class($entity_type) {
  $classes = &drupal_static(__FUNCTION__, array());
  if (!isset($classes[$entity_type])) {
	$toolbox_info          = entity_toolbox_entity_get_info($entity_type);
	$classes[$entity_type] = $toolbox_info['classes']['controllers']['inline'];
  }

  return $classes[$entity_type];
}

/**
 * Returns an entity type class file name and path.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $group
 *   The class group (controllers, entities, etc...)
 * @param string $type
 *   The class type (entity, controller, ui, etc...)
 *
 * @return array
 */
function toolbox_entity_get_class_resource($entity_type, $group, $type) {
  $resources = entity_toolbox_entity_resources_get_info($entity_type)['classes'];

  return $resources[$group][$type];
}

/**
 * Returns an entity type templates file names and paths.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $type
 *   The template type.
 *
 * @return array
 */
function toolbox_entity_get_template_resources($entity_type, $type) {
  $resources = entity_toolbox_entity_resources_get_info($entity_type)['templates'];

  return $resources[$type];
}

/**
 * Extracts the relation parameters of a reference property.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The reference property name.
 *
 * @return array
 */
function toolbox_relation_extract_parameters($entity_type, $name) {
  $toolbox_info     = entity_toolbox_entity_get_info($entity_type);
  $property         = $toolbox_info['properties'][$name];
  $rel_schema_field = $property['schemas_fields']['relation'];

  return array(
	'key_id'     => $toolbox_info['keys']['id'],
	'rel_key_id' => $rel_schema_field,
	'rel_table'  => '',
  );
}

/**
 * Returns the system path of an entity_type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $alias
 *   The menu item alias.
 *
 * @return string
 */
function entity_get_path($entity_type, $alias) {
  $toolbox_info = entity_toolbox_entity_get_info($entity_type);

  if ($alias == 'root') {
	return $toolbox_info['paths']['root'];
  }
  else {
	$aliases = array_keys($toolbox_info['paths']);
	$search  = array_search($alias, $aliases);
	$path    = $toolbox_info['paths']['root'];
	for ($i = 1; $i <= $search; $i++) {
	  $path .= '/' . $toolbox_info['paths'][$aliases[$i]];
	}

	return $path;
  }
}

/**
 * Returns an entity type admin path.
 *entity_toolbox_
 * @param string $entity_type
 *   The entity type.
 *
 * @return string
 */
function entity_admin_path($entity_type) {
  $toolbox_info = entity_toolbox_entity_get_info($entity_type);

  return $toolbox_info['paths']['root'] . '/' . $toolbox_info['paths']['admin'];
}

/**
 * Returns an entity type action path, such as edit, add, etc...
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $action
 *   The action type.
 *
 * @return string
 */
function entity_action_path($entity_type, $action) {

  //@todo either pre process and store the processed paths or process it on the fly.
}

/**
 * Returns the edit path of an entity.
 *
 * @param int|\EntityToolbox $entity
 *   The entity.
 * @param string             $entity_type
 *   The entity type.
 *
 * @return string
 */
function entity_edit_path($entity, $entity_type) {
  $entity      = is_numeric($entity) ? entity_load_single($entity_type, $entity) : $entity;
  $action_info = entity_toolbox_entity_action_type_get_info('edit');
  $string      = $action_info['path'];
  $wildcards   = string_extract_wildcards($action_info['path']);
  $variables   = array(
	'entity_path' => $entity->path(),
	'wildcard'    => $entity->toolboxInfo(),
  );

  return string_replace_tokens($string, $wildcards, $variables);
}

/**
 * Returns the view path of an entity.
 *
 * @param int|\EntityToolbox $entity
 *   The entity.
 * @param string             $entity_type
 *   The entity type.
 *
 * @return string
 */
function entity_view_path($entity, $entity_type) {
  $entity      = is_numeric($entity) ? entity_load_single($entity_type, $entity) : $entity;
  $action_info = entity_toolbox_entity_action_type_get_info('view');
  $string      = $action_info['path'];
  $wildcards   = string_extract_wildcards($action_info['path']);
  $variables   = array(
	'entity_path' => $entity->path(),
	'wildcard'    => $entity->toolboxInfo(),
  );

  return string_replace_tokens($string, $wildcards, $variables);
}

/**
 * Returns the delete path of an entity.
 *
 * @param int|\EntityToolbox $entity
 *   The entity.
 * @param string             $entity_type
 *   The entity type.
 *
 * @return string
 */
function entity_delete_path($entity, $entity_type) {
  $entity      = is_numeric($entity) ? entity_load_single($entity_type, $entity) : $entity;
  $action_info = entity_toolbox_entity_action_type_get_info('delete');
  $string      = $action_info['path'];
  $wildcards   = string_extract_wildcards($action_info['path']);
  $variables   = array(
	'entity_path' => $entity->path(),
	'wildcard'    => $entity->toolboxInfo(),
  );

  return string_replace_tokens($string, $wildcards, $variables);
}

/**
 * Translate an entity_toolbox property field widget type to a drupal form field type.
 *
 * @param string $widget
 *   The widget type.
 * @param bool   $multiple
 *   Whether the field allows multiple values or not. Defaults to FALSE.
 *
 * @return string
 *
 * @see hook_entity_property_info().
 */
function toolbox_widget2form_field_type($widget, $multiple = FALSE) {
  switch ($widget) {
	case 'textfield':
	  return 'textfield';
	  break;
	case 'list':
	  return 'select';
	  break;
	case 'autocomplete':
	  return 'textfield';
	  break;
	case 'textarea':
	  return 'textarea';
	  break;
	case 'checkbox':
	  return $multiple ? 'checkbox' : 'checkboxes';
	  break;
	case 'radio':
	  return $multiple ? 'radio' : 'radios';
	  break;
	default:
	  break;
  }
}

/**
 * Returns a default callback.
 *
 * @param $type
 *   The callback type.
 *
 * @return false|string
 */
function toolbox_entity_default_callback($type) {
  $callback = 'toolbox_' . $type;

  //If the function does not exist, returns FALSE, so that entity toolbox will be able to unset the callback from the build.
  return function_exists($callback) ? $callback : FALSE;
}

/**
 * Returns a default callback string.
 * If the default format callback does not exist, a generic one is returned.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $type
 *   The type of callback.
 *   (Eg : "create", "access", "uri")
 *
 * @return false|string
 */
function entity_default_callback_format($entity_type, $type) {
  $formatted = $entity_type . '_' . $type;

  return function_exists($formatted) ? $formatted : toolbox_entity_default_callback($type);
}

/**
 * Returns the default entity class for entities managed by entity_toolbox.
 *
 * @param bool   $fieldable
 *   If the entity type is fieldable.
 * @param string $class
 *   The class provided as default in hook_entity_toolbox_entity_info().
 *
 * @return string
 *
 * @see hook_entity_toolbox_entity_info().
 * @see entity_info_build().
 */
function entity_valid_class($fieldable, $class = NULL) {
  $toolbox_default = $fieldable ? 'EntityToolboxFieldableEntity' : 'EntityToolboxNotFieldableEntity';

  return class_exists($class) ? $class : $toolbox_default;
}

/**
 * Returns the default entity controller for entities managed by entity_toolbox.
 *
 * @param bool   $fieldable
 *   If the entity type is fieldable.
 * @param string $controller
 *   The controller provided as default in hook_entity_toolbox_entity_info().
 *
 * @return string
 *
 * @see hook_entity_toolbox_entity_info().
 * @see entity_info_build().
 */
function entity_valid_controller($fieldable, $controller = NULL) {
  $toolbox_default = $fieldable ? 'EntityToolboxFieldableEntityController' : 'EntityToolboxNotFieldableEntityController';

  return class_exists($controller) ? $controller : $toolbox_default;
}

/**
 * Returns the default entity controller for entities managed by entity_toolbox.
 *
 * @param bool   $fieldable
 *   If the entity type is fieldable.
 * @param string $controller
 *   The ui controller provided as default in hook_entity_toolbox_entity_info().
 *
 * @return string
 *
 * @see hook_entity_toolbox_entity_info().
 * @see entity_info_build().
 */
function entity_ui_valid_controller($fieldable, $controller = NULL) {
  $toolbox_default = $fieldable ? 'EntityToolboxFieldableUIController' : 'EntityToolboxNotFieldableUIController';

  return class_exists($controller) ? $controller : $toolbox_default;
}

/**
 * Returns the default entity inline form controller for entities managed by entity_toolbox.
 *
 * @param string $controller
 *   The inline form controller provided as default in hook_entity_toolbox_entity_info().
 *
 * @return string
 *
 * @see hook_entity_toolbox_entity_info().
 * @see entity_info_build().
 */
function entity_inline_form_valid_controller($controller = NULL) {

  return class_exists($controller) ? $controller : 'EntityToolboxInlineEntityFormController';
}

/**
 * Returns the form type of a form.
 * Eg : "my_entity_edit_form" is a form of type "edit".
 * Base types are :
 *  - Edit
 *  - Delete
 *  - Clone
 *  - Export
 *  - Inline
 *
 * @param string $form_id
 *   The form ID.
 *
 * @return string
 */
function entity_form_type($form_id) {
  $regexp = '/^(?P<entity_type>.+)_(?P<type>.+)_form$/';
  if (preg_match($regexp, $form_id, $matches)) {
	return $matches['type'];
  }
}

/**
 * Returns the entity info of an entity type, based on whether it's managed by entity toolbox or not.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 */
function reference_entity_info($entity_type) {
  $toolbox_info = entity_toolbox_entity_get_info();

  return in_array($entity_type, array_keys($toolbox_info)) ? $toolbox_info[$entity_type] : entity_get_info($entity_type);
}