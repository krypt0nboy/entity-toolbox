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
  if (in_array($entity_type, entity_toolbox_get_info())) {
    $controller = entity_toolbox_controller($entity_type);

    return $controller->getAuthor($entity);
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
  if (in_array($entity_type, entity_toolbox_get_info())) {
    $controller = entity_toolbox_controller($entity_type);

    return $controller->getAuthorUid($entity);
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
  $toolbox_info     = entity_toolbox_get_info($entity_type);
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
  $toolbox_info = entity_toolbox_get_info($entity_type);

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
  $toolbox_info = entity_toolbox_get_info();

  return in_array($entity_type, array_keys($toolbox_info)) ? $toolbox_info[$entity_type] : entity_get_info($entity_type);
}

/**
 * Returns REQUEST_TIME.
 *
 * @return int
 */
function request_time() {
  return REQUEST_TIME;
}

/**
 * Returns the current $user->uid.
 *
 * @return int
 */
function user_id() {
  global $user;

  return $user->uid;
}

/**
 * @param $var
 * @return bool
 */
function is_empty($var) {
  return empty($var);
}

/**
 * Extracts the reference properties from toolbox info.
 *
 * @param string $entity_type
 * @param array  $toolbox_info
 *
 * @return string[]
 */
function extract_reference_properties($entity_type, $toolbox_info = array()) {
  $toolbox_info = empty($toolbox_info) ? entity_toolbox_get_info($entity_type) : $toolbox_info;
  $properties   = $toolbox_info['properties'];
  $references   = array();
  foreach ($properties as $property => $info) {
    if (!empty($info['reference'])) {
      $references[] = $property;
    }
  }

  return $references;
}

/**
 * Extracts the reference properties from toolbox info.
 *
 * @param string $entity_type
 * @param array  $toolbox_info
 *
 * @return string[]
 */
function extract_parent_properties($entity_type, $toolbox_info = array()) {
  $toolbox_info = empty($toolbox_info) ? entity_toolbox_get_info($entity_type) : $toolbox_info;
  $properties   = $toolbox_info['properties'];
  $references   = array();
  foreach ($properties as $property => $info) {
    if (!empty($info['reference'])) {
      $references[] = $property;
    }
  }

  return $references;
}

/**
 * @param $entity_type
 * @return array
 */
function entity_type_get_parents($entity_type) {
}

function is_template_value($value) {
  return preg_match('/%\w+%/', $value);
}

/**
 * Returns a list of ids from a list of references.
 *
 * @param array  $references
 *   The references list.
 * @param string $reference_type
 *   The references type.
 *
 * @return integer[]
 */
function references2references_ids(array $references = array(), $reference_type) {
  if (is_array_integers($references)) {
    return $references;
  }
  else {
    $ids         = array();
    $entity_info = entity_get_info($reference_type);
    $key_id      = $entity_info['entity keys']['id'];
    foreach ($references as $key => $reference) {
      $ids[] = $reference->{$key_id};
    }

    return $ids;
  }
}

/**
 * Indicates if a variable is an entity object.
 *
 * @param mixed $var
 *   The variable to check.
 *
 * @return bool
 */
function is_entity($var) {
  $check = is_object($var);
  if ($check) {
    $class = class_parents('Entity');
  }
  else {
    return $check;
  }
}

/**
 * Returns the variable type for each key value in an array.
 *
 * @param array $array
 *   The array to check.
 *
 * @return string[]
 */
function array_values_gettype(array $array = array(), $unique = FALSE) {
  $types = array();
  foreach ($array as $key => $value) {
    $types[$key] = gettype($value);
  }

  if ($unique) {
    return array_unique(array_values($types));
  }
  else {
    return $types;
  }

}

/**
 * Returns the unique variable types an array values.
 *
 * @param array $array
 *   The array to check.
 *
 * @return string[]
 */
function array_values_gettype_unique(array $array = array()) {
  return array_values_gettype($array, TRUE);
}

/**
 * Indicates if an array values are numerics.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_numeric(array $array = array()) {
  $check = TRUE;
  reset($array);
  while (($current = current($array)) && $check) {
    $check = is_numeric($current);
    next($array);
  }

  return $check;
}

/**
 * Indicates if an array values are integers.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_integers(array $array = array()) {
  $check = TRUE;
  reset($array);
  while (($current = current($array)) && $check) {
    $check = is_integer($current);
    next($array);
  }

  return $check;
}

/**
 * Indicates if an array values are objects.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_objects(array $array = array()) {
  $check = TRUE;
  reset($array);
  while (($current = current($array)) && $check) {
    $check = is_object($current);
    next($array);
  }

  return $check;
}

/**
 * Indicates if an array values are callable functions.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_callable(array $array = array()) {
  $check = TRUE;
  reset($array);
  while (($current = current($array)) && $check) {
    $check = is_callable($current);
    next($array);
  }

  return $check;
}

/**
 * Indicates if an array values are entities.
 *
 * @param array $array
 *   The array to check.
 *
 * @return bool
 */
function is_array_entities(array $array = array()) {
  $check = TRUE;
  reset($array);
  while (($current = current($array)) && $check) {
    $check = is_entity($current);
    next($array);
  }

  return $check;
}