<?php

/**
 * Builds the info for an entity type property.
 *
 * @param array  $info
 *   The entity info passed by reference.
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *
 * @see entity_toolbox_entity_get_info().
 */
function toolbox_property_info_build(&$info, $entity_type, $name) {
  _toolbox_property_info_process($info, $entity_type, $name);
  $property = &$info['properties'][$name];
  //@todo handle property type default values
  //Creates default values for this property type.
  $default = array(
	'label'               => toolbox_property_default_label($info, $entity_type, $name),
	'description'         => toolbox_property_default_description($info, $entity_type, $name),
	'required'            => toolbox_property_default_required($info, $entity_type, $name),
	'has_revisions'       => toolbox_property_default_has_revisions($info, $entity_type, $name),
	'has_translations'    => toolbox_property_default_has_translations($info, $entity_type, $name),
	'multiple'            => toolbox_property_default_multiple($info, $entity_type, $name),
	'is_unique'           => toolbox_property_default_is_unique($info, $entity_type, $name),
	'callbacks'           => toolbox_property_default_callbacks($info, $entity_type, $name),
	'permissions'         => toolbox_property_default_permissions($info, $entity_type, $name),
	'expose'              => toolbox_property_default_expose($info, $entity_type, $name),
	//schemas names
	'schemas'             => array(),
	//field names foreach schema
	'schemas_field_names' => array(),
	//field info foreach schema
	'schemas_fields'      => array(),
	//@todo process clear
	'clear'               => array(),
  );
  toolbox_property_schema_names_info_build($info, $default, $entity_type, $name);
  toolbox_property_schema_info_build($info, $default, $entity_type, $name);
  toolbox_property_default_schemas_field_names($info, $default, $entity_type, $name);
  //Merges default values with provided ones.
  $property = array_merge($default, $property);
}

/**
 * Builds the default schema names.
 *
 * @param array  $info
 *   The entity_type info.
 * @param array  $default
 *   The default info being built by toolbox_property_info_build(), passed by reference.
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @see toolbox_property_info_build().
 */
function toolbox_property_schema_info_build($info, &$default, $entity_type, $name) {
  $property  = &$default;
  $variables = array(
	'entity_type'   => $entity_type,
	'relation_type' => !empty($info['properties'][$name]['reference']) ? $info['properties'][$name]['reference'] : NULL
  );
  foreach ($property['schemas'] as $schema_type => $schema_name) {
	$property['schemas_fields'][$schema_type] = property_type_default_schema_field($info['properties'][$name]['type'], $schema_type, $variables);
  }
}

/**
 * Builds the default schema names.
 *
 * @param array  $info
 *   The entity_type info.
 * @param array  $default
 *   The default info being built by toolbox_property_info_build(), passed by reference.
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @see toolbox_property_info_build().
 */
function toolbox_property_schema_names_info_build($info, &$default, $entity_type, $name) {
  $property                    = &$default;
  $variables                   = array(
	'entity_type'   => $entity_type,
	'relation_type' => !empty($info['properties'][$name]['reference']) ? $info['properties'][$name]['reference'] : NULL
  );
  $property['schemas']['base'] = string_template_process(entity_toolbox_schema_type_get_info('base')['name'], $variables);
  if ($info['has_revisions'] && $property['has_revisions']) {
	$property['schemas']['revision'] = string_template_process(entity_toolbox_schema_type_get_info('revision')['name'], $variables);
  }
  if ($info['properties'][$name]['type'] == 'reference' && $property['multiple']) {
	$schema_type_info                = entity_toolbox_schema_type_get_info('relation');
	$property['schemas']['relation'] = string_template_process($schema_type_info['name'], $variables);
  }
}

/**
 * Builds the property default schemas fields.
 *
 * @param array  $info
 *   The toolbox info being processed.
 * @param array  $default
 *   The default info being built by toolbox_property_info_build(), passed by reference.
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return array
 */
function toolbox_property_default_schemas_field_names($info, &$default, $entity_type, $name) {
  $property       = &$default;
  $tables         = &$property['schemas_field_names'];
  $variables      = array(
	'entity_type'   => $entity_type,
	'relation_type' => !empty($info['properties'][$name]['reference']) ? $info['properties'][$name]['reference'] : NULL
  );
  $default_base   = property_type_default_schema_field_name($info['properties'][$name]['type'], 'base', $variables);
  $tables['base'] = isset($default_base) ? $default_base : $name;
  if ($info['has_revisions'] && $property['has_revisions']) {
	$default_revision   = property_type_default_schema_field_name($info['properties'][$name]['type'], 'revision', $variables);
	$tables['revision'] = isset($default_revision) ? $default_revision : $name;
  }
}

/**
 * Builds the info for an entity type property form field.
 *
 * @param array  $info
 *   The entity_type info passed by reference.
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @see toolbox_property_info_build().
 */
function toolbox_property_form_field_info_build(&$info, $entity_type, $name) {
  $property = &$info['properties'][$name];
  $property['field'] += array(
	'widget' => 'textfield'
  );
}

/**
 * Builds the default classes for an entity type.
 *
 * @param string $entity_type
 *   The entity type machine name.
 * @param bool   $fieldable
 *   A boolean indicating if the entity type is fieldable.
 *
 * @return array
 *   An associative array where the keys are the classes type :
 *   - entities : The entity classes, having to provide at least "entity" as the default entity class, and additional classes foreach bundle.
 *   - controllers : The entity controllers.
 */
function toolbox_entity_default_classes_info_build($entity_type, $fieldable) {
  return array(
	'entities'    => array(
	  'entity' => entity_valid_class($fieldable, entity_type2entity_class($entity_type))
	),
	'controllers' => array(
	  'controller' => entity_valid_controller($fieldable, entity_type2entity_controller_class($entity_type)),
	  'ui'         => entity_ui_valid_controller($fieldable, entity_type2entity_ui_controller_class($entity_type)),
	  'inline'     => entity_inline_form_valid_controller(entity_type2entity_inline_controller_class($entity_type)),
	)
  );
}

/**
 * Builds the default callback info for an entity type.
 * Returns an array of callable functions.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return callable[]
 */
function toolbox_entity_default_callbacks_info_build($entity_type) {
  $callbacks = array();
  foreach (entity_toolbox_entity_callback_type_get_info() as $callback => $info) {
	$formatted            = preg_replace('/%entity_type%/', $entity_type, $info['name']);
	$callbacks[$callback] = function_exists($formatted) ? $formatted : $info['default'];
  }

  return $callbacks;
}

/**
 * Builds the default labels (single, plural) for an entity type.
 *
 * @param $entity_type
 *   The entity type.
 *
 * @return string[]
 */
function toolbox_entity_default_labels_info_build($entity_type) {
  return array(
	'single' => entity_type2entity_label($entity_type),
	'plural' => entity_type2entity_label_plural($entity_type)
  );
}

/**
 * Returns default entity type resources.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 */
function entity_resource_default_build($entity_type) {
  return array();
}

/**
 * Adds an action link to an entity page.
 *
 * @param array  $data
 * @param string $router_item
 * @param string $root_path
 * @param string $entity_type
 * @param string $action
 */
function toolbox_entity_action_link_add(&$data, $router_item, $root_path, $entity_type, $action) {
  if ($root_path == entity_admin_path($entity_type)) {
	$action_info = entity_toolbox_entity_action_type_get_info($action);
	$item        = menu_get_item();
  }
}

/**
 * @param $data
 * @param $router_item
 * @param $root_path
 * @param $entity_type
 * @return mixed
 */
function toolbox_entity_action_link__add(&$data, $router_item, $root_path, $entity_type) {
  if ($root_path == entity_admin_path($entity_type)) {
	$item = menu_get_item(entity_admin_path($entity_type) . '/add');
	if ($item['access']) {
	  $data['actions']['output'][] = array(
		'#theme' => 'menu_local_action',
		'#link'  => $item,
	  );
	}
  }

  return $data;
}