<?php

/**
 * @file
 *
 * This file contains functions required to build info for drupal.
 * (Eg : hook_entity_info().)
 */

/**
 * Returns build info for hook_entity_info().
 *
 * @param string $entity_type
 *   The entity type for which to build the info.
 *
 * @return array
 *
 * @see hook_entity_toolbox_entity_info().
 * @see hook_entity_info().
 */
function entity_info_build($entity_type) {
  $toolbox_info = entity_toolbox_entity_get_info($entity_type);
  /**
   * Builds info for both fieldable and non fieldable types.
   */
  $build[$entity_type] = array(
	'label'             => $toolbox_info['labels']['single'],
	'plural label'      => $toolbox_info['labels']['plural'],
	'entity class'      => toolbox_entity_get_class($entity_type),
	'controller class'  => toolbox_entity_get_controller_class($entity_type),
	'base table'        => $toolbox_info['base table'],
	'fieldable'         => $toolbox_info['fieldable'],
	'entity keys'       => $toolbox_info['keys'],
	'creation callback' => $toolbox_info['callbacks']['create'],
	'access callback'   => $toolbox_info['callbacks']['access'],
	'label callback'    => $toolbox_info['callbacks']['label'],
	'uri callback'      => $toolbox_info['callbacks']['uri'],
	'module'            => $toolbox_info['module'],
	'admin ui'          => array(
	  'path'             => entity_admin_path($entity_type),
	  //@todo handle different locations for admin files.
	  'file'             => $toolbox_info['module'] . '.' . $entity_type . '.admin.inc',
	  'controller class' => toolbox_entity_get_ui_controller_class($entity_type),
	),
  );
  /**
   * Builds info for fieldable entity types.
   * @TODO : add entity_fieldable_info_build().
   */
  if ($toolbox_info['fieldable']) {
	$build[$entity_type]['bundles']                          = array();
	$build[$entity_type]['bundle keys']                      = array(
	  'bundle' => $toolbox_info['keys']['bundle'],
	);
	$build[$entity_type]['admin ui']['menu wildcard']        = "%$entity_type";
	$build[$entity_type]['inline entity form']['controller'] = toolbox_entity_get_inline_class($entity_type);
  }
  /**
   * Builds info for non fieldable entity types.
   * @TODO : add entity_not_fieldable_info_build().
   */
  else {
	$build[$entity_type]['exportable'] = TRUE;
	$build[$entity_type]['bundle of']  = $toolbox_info['bundle of'];
  }

  return $build;
}

/**
 * Returns build info for hook_entity_info_alter().
 *
 * @param string $entity_type
 *   The entity type for which to build the info.
 * @param array  $entity_info
 *   The info to alter, passed by reference.
 *
 * @return array
 *
 * @see hook_entity_toolbox_entity_info().
 * @see hook_entity_info_alter().
 */
function entity_info_alter_build(&$entity_info, $entity_type) {

}

/**
 * Returns build info for hook_entity_property_info().
 *
 * @param string $entity_type
 *   The entity type for which to build the info.
 *
 * @return array
 *
 * @see hook_entity_toolbox_entity_info().
 * @see hook_entity_property_info().
 */
function entity_property_info_build($entity_type) {
  $toolbox_info = entity_toolbox_entity_get_info($entity_type);
  $build        = array();
  foreach ($toolbox_info['properties'] as $name => $property) {
	/**
	 * @todo process property required keys.
	 */
	$schema_field = toolbox_property_extract_schema_field($entity_type, $name);
	$build[$name] = array(
	  'label'               => $property['label'],
	  'description'         => !empty($property['description']) ? $property['description'] : NULL,
	  'type'                => toolbox_property2drupal_property($property['type'], $entity_type, $name),
	  'required'            => '',
	  //@todo : add toolbox_property_default_options_list()
	  'options list'        => '',
	  'getter callback'     => !empty($property['callbacks']['getter']) ? $property['callbacks']['getter'] : NULL,
	  'setter callback'     => !empty($property['callbacks']['setter']) ? $property['callbacks']['setter'] : NULL,
	  'validation callback' => !empty($property['callbacks']['validate']) ? $property['callbacks']['validate'] : NULL,
	  'access callback'     => !empty($property['callbacks']['access']) ? $property['callbacks']['access'] : NULL,
	  'setter permission'   => !empty($property['permissions']['setter']) ? $property['permissions']['setter'] : NULL,
	  //@todo add toolbox_property_extract_schema_field($entity_type, $name)
	  'schema field'        => !empty($schema_field) ? $schema_field : NULL,
	  'entity views field'  => TRUE,
	  'translatable'        => $property['has_translations'],
	  'clear'               => (!empty($property['reference'])) && !$property['multiple'] ? array($schema_field) : array()
	);
	/**
	 * @todo handle properties that have
	 */
	if (!empty($property['reference']) && !$property['multiple']) {
	  //@todo add entity_reference_property_info_build_numeric($entity_type, $name);
	  $build += entity_reference_property_info_build_numeric($entity_type, $name);
	}
  }

  return $build;
}

/**
 * Builds a numeric property for a reference property.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return array
 */
function entity_reference_property_info_build_numeric($entity_type, $name) {
  $property              = entity_toolbox_entity_get_info($entity_type)['properties'][$name];
  $ref_info              = reference_entity_info($property['reference']);
  $property_name         = toolbox_property_extract_schema_field($entity_type, $name);
  $build[$property_name] = array(
	'label'              => "$name ID",
	'description'        => !empty($property['description']) ? $property['description'] : NULL,
	'type'               => $property['multiple'] ? 'list<decimal>' : 'decimal',
	'required'           => '',
	//@todo : add toolbox_property_default_options_list()
	'options list'       => '',
	'entity views field' => TRUE,
	'clear'              => array($name)
  );

  return $build;
}

/**
 * Returns build info for hook_entity_property_info_alter().
 *
 * @param string $entity_type
 *   The entity type for which to build the info.
 * @param array  $info
 *   The info to alter, passed by reference.
 *
 * @return array
 *
 * @see hook_entity_toolbox_entity_info().
 * @see hook_entity_property_info_alter().
 */
function entity_property_info_alter_build(&$info, $entity_type) {
}

/**
 * Returns build info for hook_schema().
 * Builds the schema of an entity type.
 *
 * @param string $entity_type
 *   The entity type for which to build the schema.
 *
 * @return array
 *
 * @see hook_schema()
 */
function entity_schemas_build($entity_type) {
  $toolbox_info = entity_toolbox_entity_get_info($entity_type, NULL, TRUE);
  $schemas      = array();
  foreach ($toolbox_info['tables'] as $type => $name) {
	$schemas += schema_build($entity_type, $type, $name);
  }

  return $schemas;
}

/**
 * Returns build info for an entity_type table, based on its schema type callback.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $type
 *   The schema type.
 * @param string $name
 *   The schema name.
 *
 * @return array
 */
function schema_build($entity_type, $type, $name) {
  $schema_info = entity_toolbox_schema_type_get_info($type);

  return array($name => $schema_info['build callback']($entity_type));
}

/**
 * Returns build info for an entity_type base table.
 *
 * @param string $entity_type
 *   The entity type for which to build the schema.
 *
 * @return array
 *
 * @see hook_schema()
 * @see schema_build()
 * @todo add function to process name and description templates.
 */
function base_schema_build($entity_type) {
  $toolbox_info     = entity_toolbox_entity_get_info($entity_type);
  $schema_type_info = entity_toolbox_schema_type_get_info('base');
  $schema           = array(
	'description' => $schema_type_info['description'],
	'fields'      => array(),
	'primary key' => array(),
	'unique keys' => array(),
	'indexes'     => array(),
  );

  foreach ($toolbox_info['properties'] as $name => $property) {
	$schema['fields'][$property['schema_fields']['base']] = schema_field_build($entity_type, $name, 'base');
	/**
	 * @todo process primary keys, unique keys, and indexes.
	 * @todo process revision id if entity type has revisions.
	 */
  }

  return $schema;
}

/**
 * Returns build info for an entity_type revision table.
 *
 * @param string $entity_type
 *   The entity type for which to build the schema.
 *
 * @return array
 *
 * @see hook_schema()
 * @see schema_build()
 * @todo add function to process name and description templates.
 */
function revision_schema_build($entity_type) {
  $toolbox_info     = entity_toolbox_entity_get_info($entity_type);
  $schema_type_info = entity_toolbox_schema_type_get_info('revision');
  $schema           = array(
	'description' => $schema_type_info['description'],
	'fields'      => array(),
	'primary key' => array(),
	'unique keys' => array(),
	'indexes'     => array(),
  );

  foreach ($toolbox_info['properties'] as $name => $property) {
	$schema['fields'][$property['schema_fields']['revision']] = schema_field_build($entity_type, $name, 'revision');
	/**
	 * @todo process primary keys, unique keys, and indexes.
	 * @todo process revision id if entity type has revisions.
	 */
  }

  return $schema;
}

/**
 * Returns build info for an entity_type relation table.
 *
 * @param string $entity_type
 *   The entity type for which to build the schema.
 *
 * @return array
 *
 * @see hook_schema()
 * @see schema_build()
 * @todo add function to process name and description templates.
 */
function relation_schema_build($entity_type) {
  $toolbox_info     = entity_toolbox_entity_get_info($entity_type);
  $schema_type_info = entity_toolbox_schema_type_get_info('relation');
  $schema           = array(
	'description' => $schema_type_info['description'],
	'fields'      => array(),
	'primary key' => array(),
	'unique keys' => array(),
	'indexes'     => array(),
  );

  foreach ($toolbox_info['properties'] as $name => $property) {
	$schema['fields'][$property['schema_fields']['revision']] = schema_field_build($entity_type, $name, 'revision');
	/**
	 * @todo process primary keys, unique keys, and indexes.
	 * @todo process revision id if entity type has revisions.
	 */
  }

  return $schema;
}

/**
 * Returns build info for an entity schema field.
 *
 * @param string $entity_type
 *   The entity type for which to build the info.
 * @param string $name
 *   The property name for which the build the schema field.
 * @param string $schema_type
 *   The schema type for which the field is being built.
 *
 * @return array
 */
function schema_field_build($entity_type, $name, $schema_type) {
  $toolbox_info = entity_toolbox_entity_get_info($entity_type);
}

/**
 * Returns build info for hook_schema_alter().
 *
 * @param array  $schema
 *   The schema to alter, passed by reference.
 * @param string $entity_type
 *   The entity type for which to alter the schema.
 *
 * @see hook_schema_alter().
 */
function schema_alter_build(&$schema, $entity_type) {

}

/**
 * Builds the indexes for an entity table.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $type
 *   The schema type.
 * @param string $name
 *   The schema name.
 *
 * @return string[]
 */
function schema_indexes_build($entity_type, $type, $name) {
}

/**
 * Returns build info for hook_permissions().
 *
 * @param string $entity_type
 *   The entity type for which to build the permissions.
 *
 * @return array
 *
 * @see hook_permissions().
 */
function permissions_build($entity_type) {

}

/**
 * Returns build info for @see hook_menu_local_tasks_alter().
 *
 * @param        $data
 * @param        $router_item
 * @param        $root_path
 * @param string $entity_type
 *   The entity type for which to build the info.
 *
 * @see hook_menu_local_tasks_alter().
 */
function menu_local_tasks_alter_build(&$data, $router_item, $root_path, $entity_type) {
  toolbox_entity_action_link__add($data, $router_item, $root_path, $entity_type);
}

/**
 * Views related data builds.
 */

/**
 * Returns build info for hook_views_data.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 */
function views_data_build($entity_type) {
  $toolbox_info  = entity_toolbox_entity_get_info($entity_type);
  $base_table    = $toolbox_info['base table'];
  $data          = array($base_table => array());
  $schema_fields = toolbox_info_extract_schema_fields($entity_type);
  foreach ($toolbox_info['properties'] as $name => $property) {
	$schema_field                     = $schema_fields[$name];
	$data[$base_table][$schema_field] = views_data_property_field_build($entity_type, $name);
  }
  $data += views_data_operations_links_build($entity_type);

  return $data;
}

/**
 * Returns the build data for an entity property field in views.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return array
 */
function views_data_property_field_build($entity_type, $name) {
  $toolbox_info       = entity_toolbox_entity_get_info($entity_type);
  $property_info      = $toolbox_info['properties'][$name];
  $property_type_info = entity_toolbox_property_type_get_info($property_info['type']);
  $handlers_callback  = $property_type_info['default_views_handlers'];
  $data               = array();
  $data['title']      = t($property_info['label']);
  $data['help']       = t($property_info['description']);
  $data += $handlers_callback();
  if (($property_info['type'] == 'parent' && 'reference') && !$property_info['multiple']) {
	$data['relationship'] = views_data_property_relationship_build($entity_type, $name);
  }

  //@todo handle custom fields

  return $data;
}

/**
 * Returns the build data for a relationship.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return array
 */
function views_data_property_relationship_build($entity_type, $name) {
  $toolbox_info  = entity_toolbox_entity_get_info($entity_type);
  $property_info = $toolbox_info['properties'][$name];
  list($rel_table, $rel_key_id) = array();
  $title = $property_info['label'];
  $label = $property_info['label'] . ' (relationship)';
  $help  = $property_info['description'] . ' (relationship)';

  return array(
	'base'       => $rel_table,
	'base field' => $rel_key_id,
	'handler'    => 'views_handler_relationship',
	'label'      => t($label),
	'title'      => t($title),
	'help'       => t($help),
  );
}

/**
 * Returns build info for operations links in views.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 *
 * @see hook_toolbox_action_type_info().
 */
function views_data_operations_links_build($entity_type) {
  //@todo hook_views_data_operations_links_prebuild().
  $data               = array();
  $data['operations'] = views_data_operations_link_build($entity_type);
  views_data_operation_link_build($data, $entity_type, 'edit');
  views_data_operation_link_build($data, $entity_type, 'view');
  views_data_operation_link_build($data, $entity_type, 'delete');
}

/**
 * Returns build info for an operation link in views.
 *
 * @param array  $data
 *   The data to build on.
 * @param string $entity_type
 *   The entity type.
 * @param string $operation
 *   The operation type.
 *
 * @return array
 */
function views_data_operation_link_build(&$data, $entity_type, $operation) {
  $action_info = entity_toolbox_entity_action_type_get_info($operation);
  //process string
  $link  = '%operation%_%entity_type%';
  $title = ucfirst($operation) . 'link';
  //process string
  $help = 'Provides a link to %action_type% the %entity_type%.';

  $data[$link] = array(
	'title'   => t($title),
	'help'    => t($help),
	'handler' => $action_info['default_views_handler'],
	'type'    => $entity_type,
  );
}

/**
 * Returns build info for an operations link in views.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 */
function views_data_operations_link_build($entity_type) {
  return array(
	'title'   => t('Operations links'),
	'help'    => t('Display all operations available for this ' . $entity_type),
	'handler' => 'entity_toolbox_handler_entity_operations_field',
	'type'    => $entity_type
  );
}

/**
 * Builds the default admin view for the entity type.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return \view
 */
function views_default_admin_view_build($entity_type) {
  $view = new view();
}