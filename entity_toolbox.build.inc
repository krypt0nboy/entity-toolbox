<?php

/**
 * @file
 *
 * This file contains functions required to build info for drupal.
 * (Eg : hook_entity_info().)
 */

/**
 * Returns a built hook data.
 *
 * @param string $hook
 *   The hook name.
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 */
function hook_build($hook, $entity_type) {
  if ($hook != 'entity_toolbox_info') {
    $hook_info = entity_toolbox_hook_get_info($hook);
    $function  = $hook_info['build callback'];

    return $function($entity_type);
  }
}

/**
 * Returns build info for hook_entity_info().
 *
 * @param string $entity_type
 *   The entity type for which to build the info.
 *
 * @return array
 *
 * @see hook_entity_toolbox_info().
 * @see hook_entity_info().
 */
function entity_info_build($entity_type) {
  $toolbox_info = entity_toolbox_get_info($entity_type);
  $builder      = $toolbox_info['fieldable'] ? new EntityToolboxInfoBuilderFieldable($entity_type) : new EntityToolboxInfoBuilderNotFieldable($entity_type);

  return $builder->build();
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
function schema_build($entity_type) {

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

}