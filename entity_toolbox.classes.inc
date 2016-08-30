<?php

/**
 * Returns the toolbox entity controller for an entity type.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $bundle
 *   The entity bundle, or NULL to use the entity type default controller.
 *
 * @return \EntityToolboxController
 */
function entity_toolbox_controller($entity_type, $bundle = NULL) {
  $controllers = &drupal_static(__FUNCTION__, array());
  if (!isset($controllers[$entity_type])) {
    $type_info = entity_toolbox_get_info($entity_type);
    $class     = $type_info['classes']['controller'];
    /** @var \EntityToolboxController */
    $controllers[$entity_type] = new $class($entity_type);
  }

  return $controllers[$entity_type];
}

/**
 * Return the toolbox ui controller for a entity type.
 *
 * @param $entity_type
 *   The entity type.
 *
 * @return \EntityToolboxUIController
 */
function entity_toolbox_ui_controller($entity_type) {
  if (in_array($entity_type, entity_toolbox_get_info())) {
    return entity_ui_controller($entity_type);
  }
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
    $toolbox_info          = entity_toolbox_get_info($entity_type);
    $classes[$entity_type] = $toolbox_info['classes']['entity'];
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
    $toolbox_info          = entity_toolbox_get_info($entity_type);
    $classes[$entity_type] = $toolbox_info['classes']['controller'];
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
    $toolbox_info          = entity_toolbox_get_info($entity_type);
    $classes[$entity_type] = $toolbox_info['classes']['ui controller'];
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
    $toolbox_info          = entity_toolbox_get_info($entity_type);
    $classes[$entity_type] = $toolbox_info['classes']['inline form controller'];
  }

  return $classes[$entity_type];
}