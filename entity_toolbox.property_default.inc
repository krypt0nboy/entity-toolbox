<?php

/**
 * @file
 *
 * This file contains functions to get the default values for properties info.
 */

/**
 * Returns a default property toolbox info key data.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 * @param string $key
 *   The key.
 * @param array  $info
 *   The retrieved toolbox info.
 *
 * @return mixed
 */
function toolbox_property_default__($entity_type, $name, $key, $info) {
  $property_info      = $info['properties'][$name];
  $property_type_info = entity_toolbox_property_type_get_info($property_info['type']);
  $key_               = 'default_' . $key;

  if (!empty($property_type_info[$key_])) {
	$variables = array(
	  'entity_type' => $entity_type,
	  'reference'   => !empty($property_info['reference'])
	);

	return string_template_process($property_type_info[$key_], $variables);
  }
}

/**
 * Returns an property default label.
 *
 * @param array  $info
 *   The entity type info retrieved by entity toolbox.
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return string
 */
function toolbox_property_default_label($info, $entity_type, $name) {
  $property_info      = $info['properties'][$name];
  $property_type_info = entity_toolbox_property_type_get_info($property_info['type']);

  return !empty($property_type_info['default_label']) ? string_template_process($property_type_info['default_label'], array('entity_type' => $entity_type)) : ucfirst(preg_replace('/_/', ' ', $name));
}

/**
 * Returns a property default description.
 *
 * @param array  $info
 *   The entity type info retrieved by entity toolbox.
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return string
 */
function toolbox_property_default_description($info, $entity_type, $name) {
  $property_info      = $info['properties'][$name];
  $property_type_info = entity_toolbox_property_type_get_info($property_info['type']);

  return !empty($property_type_info['default_description']) ? string_template_process($property_type_info['default_description'], array('entity_type' => $entity_type)) : '';
}

/**
 * Returns the default required info for a property.
 *
 * @param array  $info
 *   The toolbox entity info.
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return array
 */
function toolbox_property_default_required($info, $entity_type, $name) {
  return property_type_default_required($info['properties'][$name]['type']);
}

/**
 * Returns the default "has_revisions" info for a property.
 *
 * @param array  $info
 *   The toolbox entity info.
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return bool
 */
function toolbox_property_default_has_revisions($info, $entity_type, $name) {
  return FALSE;
}

function toolbox_property_default_has_translations($info, $entity_type, $name) {
  return FALSE;
}

function toolbox_property_default_multiple($info, $entity_type, $name) {
  return FALSE;
}

function toolbox_property_default_is_unique($info, $entity_type, $name) {
  return FALSE;
}

function toolbox_property_default_callbacks($info, $entity_type, $name) {
  return array();
}

function toolbox_property_default_permissions($info, $entity_type, $name) {
  return array();
}

function toolbox_property_default_expose($info, $entity_type, $name) {
  return TRUE;
}

/**
 * Returns the default label when building a property toolbox info.
 *
 * @param string $type
 *   The property type.
 *
 * @return string
 */
function property_type_default_label($type) {
  $type_info = entity_toolbox_property_type_get_info($type);

}

/**
 * Returns the default description when building a property toolbox info.
 *
 * @param string $type
 *   The property type.
 *
 * @return string
 */
function property_type_default_description($type) {
  $type_info = entity_toolbox_property_type_get_info($type);

}

/**
 * Returns the default "required" value when building a property toolbox info.
 *
 * @param string $type
 *   The property type. ("Eg : "id", "bundle", "tiny_text").
 *
 * @return array
 */
function property_type_default_required($type) {
  $type_info = entity_toolbox_property_type_get_info($type);

  return array();
}

/**
 * Returns the default "has_revisions' value when building a property toolbox info.
 *
 * @param string $type
 *   The property type. ("Eg : "id", "bundle", "tiny_text").
 *
 * @return bool
 */
function property_type_default_has_revisions($type) {
  $type_info = entity_toolbox_property_type_get_info($type);

  return !empty($type_info['default_has_revisions']) ? $type_info['default_has_revisions'] : FALSE;
}

/**
 * Returns the default "has_translations' value when building a property toolbox info.
 *
 * @param string $type
 *   The property type. ("Eg : "id", "bundle", "tiny_text").
 *
 * @return bool
 */
function property_type_default_has_translations($type) {
  $type_info = entity_toolbox_property_type_get_info($type);

  return !empty($type_info['default_has_translations']) ? $type_info['default_has_translations'] : FALSE;
}

/**
 * Returns the default "multiple' value when building a property toolbox info.
 *
 * @param string $type
 *   The property type. ("Eg : "id", "bundle", "tiny_text").
 *
 * @return bool
 */
function property_type_default_multiple($type) {
  $type_info = entity_toolbox_property_type_get_info($type);

  return FALSE;
}

/**
 * Returns the default "callbacks" value when building a property toolbox info.
 *
 * @param string $type
 *   The property type. ("Eg : "id", "bundle", "tiny_text").
 *
 * @return array
 */
function property_type_default_callbacks($type) {
  $type_info = entity_toolbox_property_type_get_info($type);

  return array(
	'getter' => 'entity_toolbox_multi_value_property_get',
	'setter' => 'entity_toolbox_multi_value_property_set'
  );
}

/**
 * Returns the default "permissions" value when building a property toolbox info.
 *
 * @param string $type
 *   The property type. ("Eg : "id", "bundle", "tiny_text").
 *
 * @return array
 */
function property_type_default_permissions($type) {
  $type_info = entity_toolbox_property_type_get_info($type);

  return array();
}

/**
 * Returns the default "expose" value when building a property toolbox info.
 *
 * @param string $type
 *   The property type. ("Eg : "id", "bundle", "tiny_text").
 *
 * @return array
 */
function property_type_default_expose($type) {
  $type_info = entity_toolbox_property_type_get_info($type);

  return array();
}

/**
 * Returns a default schema field name for a schema.
 *
 * @param string $type
 *   The property type.
 * @param string $schema_type
 *   The schema type.
 * @param array  $variables
 *   The variables to be processed.
 *
 * @return null|string
 */
function property_type_default_schema_field_name($type, $schema_type, $variables = array()) {
  $type_info = entity_toolbox_property_type_get_info($type);

  return !empty($type_info['default_schemas_fields'][$schema_type]) ? string_template_process($type_info['default_schemas_fields'][$schema_type], $variables) : NULL;
}

/**
 * Returns a default schema field.
 *
 * @param string $type
 *   The property type.
 * @param string $schema_type
 *   The schema type.
 * @param array  $variables
 *   The variables to process.
 *
 * @return array
 */
function property_type_default_schema_field($type, $schema_type, $variables = array()) {
  $type_info = entity_toolbox_property_type_get_info($type);

  //@todo process templates
  return !empty($type_info['default_schema'][$schema_type]) ? $type_info['default_schema'][$schema_type] : NULL;
}

/**
 * Returns a property type default value.
 *
 * @param string $type
 *   The property type.
 *
 * @return mixed
 */
function toolbox_property_default_value($type) {
  $type_info = entity_toolbox_property_type_get_info($type);

  return $type_info['default_value'];
}