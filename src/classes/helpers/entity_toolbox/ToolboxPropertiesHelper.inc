<?php

require_once 'EntityToolboxHelperBase.inc';

/**
 * Class ToolboxPropertiesHelper
 */
class ToolboxPropertiesHelper extends EntityToolboxHelperBase {
  use EntityToolboxPropertiesDependentTraits;
  /**
   * @var array $requiredSchemaPropertyTypes
   *   The property types required for this schema type.
   */
  protected $requiredSchemaPropertyTypes = array();
  /** {{@inheritdoc}} */
  const ALIAS = 'properties';

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'required_schema_property_types' => array(
        'entity_id'          => TRUE,
        'entity_revision_id' => TRUE,
        'translation_set_id' => TRUE,
      )
    ), $args);
    parent::__construct($args);
  }

  /**
   * @return array
   */
  public function getRequiredSchemaPropertyTypes() {
    return $this->requiredSchemaPropertyTypes;
  }

  /**
   * @param array $requiredSchemaPropertyTypes
   */
  public function setRequiredSchemaPropertyTypes($requiredSchemaPropertyTypes) {
    $this->requiredSchemaPropertyTypes = $requiredSchemaPropertyTypes;
  }

  /**
   * Returns a property.
   *
   * @param string $name
   *   The property name.
   *
   * @return array
   */
  public function propGet($name) {
    $props = $this->alias();

    return $props[$name];
  }

  /*** ISSERS ***/

  /**
   * Indicates if a property is required.
   *
   * @param string $name
   *   The property name.
   *
   * @return bool
   */
  public function propIsRequired($name) {
    $prop = $this->propGet($name);

    return $prop['required'];
  }

  /**
   * Indicates if a property is required.
   *
   * @param string $name
   *   The property name.
   *
   * @return bool
   */
  public function propIsMulti($name) {
    $prop = $this->propGet($name);

    return $prop['multiple'];
  }

  /**
   * Indicates if a property is required.
   *
   * @param string $name
   *   The property name.
   *
   * @return bool
   */
  public function propIsSerialized($name) {
    $prop = $this->propGet($name);

    return $prop['serialize'];
  }

  /**
   * Indicates if a property is required.
   *
   * @param string $name
   *   The property name.
   *
   * @return bool
   */
  public function propIsIdProperty($name) {
    $prop = $this->propGet($name);

    return $prop['type'] == 'entity_id';
  }

  /**
   * Indicates if a property is required.
   *
   * @param string $name
   *   The property name.
   *
   * @return bool
   */
  public function propIsRevisionProperty($name) {
    $prop = $this->propGet($name);

    return $prop['type'] == 'entity_revision_id';
  }

  /**
   * Indicates if a property is required.
   *
   * @param string $name
   *   The property name.
   *
   * @return bool
   */
  public function propIsBundleProperty($name) {
    $prop = $this->propGet($name);

    return $prop['type'] == 'entity_bundle';
  }

  /**
   * Indicates if a property is required.
   *
   * @param string $name
   *   The property name.
   *
   * @return bool
   */
  public function propIsReference($name) {
    $prop = $this->propGet($name);

    return !empty($prop['reference']);
  }

  /**
   * Indicates if a property is required.
   *
   * @param string $name
   *   The property name.
   *
   * @return bool
   */
  public function propIsSelfReference($name) {
    $ref = $this->propGetReference($name);
    if (isset($ref)) {
      return $ref == $this->entityType;
    }

    return FALSE;
  }

  /**
   * Indicates if a property is required.
   *
   * @param string $name
   *   The property name.
   *
   * @return bool
   */
  public function propIsParent($name) {
    $prop     = $this->propGet($name);
    $isParent = !empty($prop['is_parent']) ? $prop['is_parent'] : FALSE;
    if (!$isParent) {
      $type = $this->propGetType($name);

      return ($type == 'parent') || ($type = 'self_parent');
    }

    return $isParent;
  }

  /**
   * Indicates if a property is required for schemas.
   *
   * @param string $name
   *   The property name.
   *
   * @return bool
   */
  public function propIsRequiredForSchema($name) {
    $prop = $this->propGet($name);
    $type = $prop['type'];

    return in_array($type, array_keys($this->requiredSchemaPropertyTypes));
  }

  /*** ISSERS END ***/

  /*** HASSERS ***/

  /**
   * Indicates if a property has a field for a given schema type.
   *
   * @param string $name
   *   The property name.
   * @param string $schemaType
   *   The schema type.
   *
   * @return bool
   */
  public function propHasSchemaFieldName($name, $schemaType) {
    $prop = $this->propGet($name);

    return !empty($prop['schemas_fields_name'][$schemaType]);
  }

  /*** HASSERS END ***/

  /**
   * Returns the toolbox property type.
   *
   * @param string $name
   *   The property name.
   *
   * @return string
   */
  public function propGetType($name) {
    $prop = $this->propGet($name);

    return $prop['type'];
  }

  /**
   * Returns the property reference.
   *
   * @param string $name
   *   The property name.
   *
   * @return null|string
   */
  public function propGetReference($name) {
    $prop = $this->propGet($name);
    if ($this->propIsReference($name)) {

      return $prop['reference'];
    }
    else {
      return NULL;
    }
  }
}