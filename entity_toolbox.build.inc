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
 * @param $arg
 *
 * @return HookBuilder
 */
function hook_get_builder($hook, $arg) {
  return hook_get_builder_factory($hook, $arg)->getInstance();
}

/**
 * Returns a hook builder factory.
 *
 * @param $hook
 * @param $args
 *
 * @return HookBuilderFactory
 */
function hook_get_builder_factory($hook, array $args = array()) {
  require_once 'src/classes/factories/EntityToolboxDependentHookBuilderFactory.inc';
  $args += array('hook' => $hook);
  $hook_info    = entity_toolbox_hook_get_info($hook);
  $factoryClass = $hook_info['factory class'];
  $factory      = new $factoryClass($args);

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
  $instanceArgs = array(
    'entity_type' => $entity_type,
  );
  $factoryArgs  = array(
    'entity_type'   => $entity_type,
    'instance_args' => $instanceArgs
  );
  $builder      = hook_get_builder('entity_info', $factoryArgs);

  return $builder->build();
}

/**
 * @param $entity_type
 * @return array
 */
function entity_info_retrieve($entity_type) {
  $toolbox_info = entity_toolbox_get_info($entity_type);

  return array($entity_type => $toolbox_info['entity_info']);
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
  $instanceArgs = array(
    'entity_type' => $entity_type,
  );
  $factoryArgs  = array(
    'entity_type'   => $entity_type,
    'instance_args' => $instanceArgs
  );
  $builder      = hook_get_builder('entity_property_info', $factoryArgs);
  $build        = array($entity_type => $builder->build());

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
  $instanceArgs = array(
    'entity_type' => $entity_type,
  );
  $factoryArgs  = array(
    'entity_type'   => $entity_type,
    'instance_args' => $instanceArgs
  );
  $builder      = hook_get_builder('schema', $factoryArgs);

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
function schema_alter_build(&$schema, $entity_type) {}

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
  $instanceArgs = array(
    'entity_type' => $entity_type,
  );
  $factoryArgs  = array(
    'entity_type'   => $entity_type,
    'instance_args' => $instanceArgs
  );
  $builder      = hook_get_builder('permissions', $factoryArgs);

  return $builder->build();
}

/**
 * Returns build info for hook_entity_operation_info().
 *
 * @param string $entity_type
 *   The entity type for which to build the permissions.
 *
 * @return array
 *
 * @see hook_entity_operation_info().
 */
function entity_operation_info_build($entity_type) {
  $instanceArgs = array(
    'entity_type' => $entity_type,
  );
  $factoryArgs  = array(
    'entity_type'   => $entity_type,
    'instance_args' => $instanceArgs
  );
  $builder      = hook_get_builder('entity_operation_info', $factoryArgs);
  $build        = array($entity_type => $builder->build());

  return $build;
}

/**
 * Returns build info for hook_menu().
 *
 * @param string $module
 *   The module for which to build the menu items.
 *
 * @return array
 *
 * @see hook_menu().
 */
function menu_build($module) {
  $instanceArgs = array(
    'module' => $module,
  );
  $factoryArgs  = array(
    'instance_args' => $instanceArgs
  );
  $builder      = hook_get_builder('menu', $factoryArgs);

  return $builder->build();
}

/**
 * Returns build info for hook_theme().
 *
 * @param string      $module
 *   The module for which to build the theme items.
 * @param null|string $group
 *   The entity group for which to build the theme items.
 *   If null, the builder will return themes for all the module's entities.
 *
 * @return array
 *
 * @see hook_theme().
 */
function entities_group_menu_build($module, $group = NULL) {
  $instanceArgs = array(
    'module' => $module,
  );
  $factoryArgs  = array(
    'instance_args' => $instanceArgs
  );
  /** @var MenuBuilder $builder */
  $builder = hook_get_builder('menu', $factoryArgs);

  return $builder->buildEntityGroupMenus($group);
}

/**
 * Returns build info for hook_theme().
 *
 * @param string $module
 *   The module for which to build the theme items.
 *
 * @return array
 *
 * @see hook_theme().
 */
function theme_build($module) {
  $instanceArgs = array(
    'module' => $module,
  );
  $factoryArgs  = array(
    'instance_args' => $instanceArgs
  );
  $builder      = hook_get_builder('theme', $factoryArgs);

  return $builder->build();
}

/**
 * Returns build info for hook_theme().
 *
 * @param string      $module
 *   The module for which to build the theme items.
 * @param null|string $entity_type
 *   The entity for which to build the theme items.
 *   If null, the builder will return themes for all the module's entities.
 *
 * @return array
 *
 * @see hook_theme().
 */
function entities_theme_build($module, $entity_type = NULL) {
  $instanceArgs = array(
    'module' => $module,
  );
  $factoryArgs  = array(
    'instance_args' => $instanceArgs
  );
  /** @var ThemeBuilder $builder */
  $builder = hook_get_builder('theme', $factoryArgs);

  return $builder->buildEntityThemes($entity_type);
}

/**
 * Returns build info for hook_permission().
 *
 * @param string $module
 *   The module for which to build the permissions.
 *
 * @return array
 *
 * @see hook_permission().
 */
function permission_build($module) {
  $instanceArgs = array(
    'module' => $module,
  );
  $factoryArgs  = array(
    'module'        => $module,
    'instance_args' => $instanceArgs
  );
  $builder      = hook_get_builder('permission', $factoryArgs);

  return $builder->build();
}

/**
 * Returns build info for hook_permission().
 *
 * @param string      $module
 *   The module for which to build the permission.
 * @param null|string $entity_type
 *   The entity for which to build the permission.
 *   If null, the builder will return themes for all the module's entities.
 *
 * @return array
 *
 * @see hook_permission().
 */
function entities_permission_build($module, $entity_type = NULL) {
  $instanceArgs = array(
    'module' => $module,
  );
  $factoryArgs  = array(
    'instance_args' => $instanceArgs
  );
  /** @var PermissionBuilder $builder */
  $builder = hook_get_builder('permission', $factoryArgs);

  return $builder->buildEntitiesPermissions($entity_type);
}

/**
 * Returns build info for hook_hook_info().
 *
 * @param string $module
 *   The module for which to build the hooks.
 *
 * @return array
 *
 * @see hook_hook_info().
 */
function hook_info_build($module) {
  $instanceArgs = array(
    'module' => $module,
  );
  $factoryArgs  = array(
    'module'        => $module,
    'instance_args' => $instanceArgs
  );
  $builder      = hook_get_builder('hook_info', $factoryArgs);

  return $builder->build();
}