<?php

/**
 * Class EntityToolboxControllerFieldable
 * Used for fieldable entities.
 */
class EntityToolboxControllerFieldable extends EntityToolboxController {

  /**
   * @var array $inheritableFields
   *   An array of fields to be inherited by children entities.
   */
  protected $inheritableFields;

  /**
   * @var  array $inheritedFields
   *   An associative array whose keys are the fields to inherit from parent
   *   entities, and the values the parent(s) from which to inherit the field.
   */
  protected $inheritedFields;

  /**
   * {@inheritdoc}
   */
  public function __construct($entity_type) {
    parent::__construct($entity_type);
    $this->setBundles();
    $this->setInheritableFields();
    $this->setInheritedFields();
  }

  /**
   * Retrieves the inheritable fields for the set entity bundle.
   */
  protected function setInheritableFields() {
    foreach (entity_toolbox_inheritable_field_get_info($this->entityType) as $bundle => $fields) {
      foreach ($fields as $field => $info) {
        $this->inheritableFields[$bundle][] = $field;
      }
    }
  }

  /**
   * Returns inheritable fields for the set entity bundle.
   *
   * @param string $bundle
   *   The entity bundle.
   *
   * @return array
   */
  public function inheritableFields($bundle) {
    return $this->inheritableFields[$bundle];
  }

  /**
   * Retrieves the inherited fields for the set entity bundle.
   */
  protected function setInheritedFields() {
    foreach (entity_toolbox_inherited_field_get_info($this->entityType) as $bundle => $fields) {
      foreach ($fields as $field => $inherited_from) {
        $this->inheritableFields[$bundle][$field] = $inherited_from;
      }
    }
  }

  /**
   * Returns the inherited field for the set entity bundle.
   *
   * @param string $bundle
   *   The entity bundle.
   *
   * @return array
   */
  public function InheritedFields($bundle) {
    return $this->inheritedFields[$bundle];
  }
}