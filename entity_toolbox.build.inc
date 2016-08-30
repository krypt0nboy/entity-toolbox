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
  $hook_info = entity_toolbox_hook_get_info($hook);

  return $hook_info['build callback']($entity_type);
}

/**
 * Returns a hook builder.
 *
 * @param $hook
 * @param $entity_type
 *
 * @return HookBuilder
 */
function hook_get_builder($hook, $entity_type) {
  return hook_get_builder_factory($hook, $entity_type)->getInstance();
}

/**
 * Returns a hook builder factory.
 *
 * @param $hook
 * @param $entity_type
 *
 * @return HookBuilderFactory
 */
function hook_get_builder_factory($hook, $entity_type) {
  $factory = new ContribHookBuilderFactory($hook, $entity_type);

  return $factory;
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
  $builder = hook_get_builder('entity_info', $entity_type);
  $build   = array($entity_type => $builder->build());

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
  $builder = hook_get_builder('entity_property_info', $entity_type);
  $build   = array($entity_type => $builder->build());

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
function schema_build($entity_type) {
  $builder = hook_get_builder('schema', $entity_type);

  return $builder->build();
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
  $builder = hook_get_builder('permissions', $entity_type);

  return $builder->build();
}

/**
 * Returns build info for hook_operations_info().
 *
 * @param string $entity_type
 *   The entity type for which to build the permissions.
 *
 * @return array
 *
 * @see hook_operations_info().
 */
function operations_info_build($entity_type) {
  $builder = hook_get_builder('operations', $entity_type);

  return $builder->build();
}