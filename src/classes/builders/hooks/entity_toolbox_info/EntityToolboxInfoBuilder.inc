<?php

/**
 * Class EntityToolboxInfoBuilder
 *
 * Base build class for hook_entity_toolbox_info().
 */
class EntityToolboxInfoBuilder extends HookBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct('entity_toolbox_info', $entityType, $rawData);
  }

  /** {{@inheritdoc}} */
  protected function setValuesBuilders() {
    parent::setValuesBuilders();
    $this->valuesBuilders['entity_type'] = new EntityTypeValueBuilder($this->entityType, $this->rawData);
    $this->valuesBuilders['labels']      = new LabelsValueBuilder($this->entityType, $this->rawData);
    $this->valuesBuilders['classes']     = new ClassesValueBuilder($this->entityType, $this->rawData);
  }

  /** {{@inheritdoc}} */
  public function build() {
    $this->processedData['entity_type'] = $this->getValueBuilder('entity_type')
                                               ->build();
    $this->processedData['labels']      = $this->getValueBuilder('labels')
                                               ->build();
    $this->processedData['classes']     = $this->getValueBuilder('classes')
                                               ->build();

    return array_merge($this->processedData, $this->rawData);
  }

}