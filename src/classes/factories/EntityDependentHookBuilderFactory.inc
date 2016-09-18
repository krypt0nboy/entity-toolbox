<?php

/**
 * Class EntityDependentHookBuilderFactory
 */
class EntityDependentHookBuilderFactory extends HookBuilderFactory {
  /**
   * @var string $entityType
   */
  protected $entityType;
  /**
   * @var bool $fieldable
   */
  protected $fieldable;

  /**
   * @return string
   */
  public function getEntityType() {
    return $this->entityType;
  }

  /**
   * @param string $entityType
   */
  public function setEntityType($entityType) {
    $this->entityType = $entityType;
  }

  /**
   * @return boolean
   */
  public function getFieldable() {
    return $this->fieldable;
  }

  /**
   * @param boolean $fieldable
   */
  public function setFieldable($fieldable) {
    $this->fieldable = $fieldable;
  }

  /**
   *
   */
  protected function initTemplateVars() {
    $this->updateTemplateVar('entity_type', $this->entityType);
    $this->updateTemplateVar('fieldable', $this->fieldable ? 'Fieldable' : 'NotFieldable');
  }


}