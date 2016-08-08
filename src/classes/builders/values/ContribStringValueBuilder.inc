<?php

/**
 * Class ContribStringValueBuilder
 */
class ContribStringValueBuilder extends StringValueBuilder {
  /**
   * @var array $toolboxInfo
   *   The entity type toolbox info.
   */
  protected $toolboxInfo = array();

  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey, $defaultValue = NULL, $defaultValueIsTemplate = NULL, array $templateVariables = array()) {
    parent::__construct($entityType, $tableKey, array(), $defaultValue, $defaultValueIsTemplate, $templateVariables);
    $this->toolboxInfo = entity_toolbox_get_info($this->entityType);
  }
}