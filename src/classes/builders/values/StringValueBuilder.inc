<?php

/**
 * Class StringValueBuilder
 */
class StringValueBuilder extends ValueBuilder {
  /**
   * @var mixed $defaultValue
   *   The default value to be set. Can be a string template.
   *
   * @see string_template_process().
   */
  protected $defaultValue;

  /**
   * @var bool $defaultValueIsTemplate
   *   Indicates if the default value needs to be processed by string_process_template().
   */
  protected $defaultValueIsTemplate;

  /**
   * @var array $templateVariables
   *   An associative array containing the array passed to string_process_template().
   */
  protected $templateVariables = array();

  /**
   * StringValueBuilder constructor.
   * @param null|string $entityType
   * @param null|string $tableKey
   * @param array       $rawData
   * @param mixed       $defaultValue
   *   The default value to be set if needed.
   * @param bool        $defaultValueIsTemplate
   *   Indicates if the default value should be processed as a template.
   * @param array       $templateVariables
   *   The variables to be accessed by string_process_template when processing the default value.
   */
  public function __construct($entityType, $tableKey, array $rawData = array(), $defaultValue = NULL, $defaultValueIsTemplate = NULL, array $templateVariables) {
    parent::__construct($entityType, $tableKey, $rawData);
    if (isset($defaultValue)) {
      $this->defaultValue           = $defaultValue;
      $this->defaultValueIsTemplate = isset($defaultValueIsTemplate) ? $defaultValueIsTemplate : preg_match('/%\w+%/', $defaultValue);
    }
  }

  /**
   * @return string
   */
  public function build() {
  }

  /**
   * Builds the default value to be merged in the method build().
   *
   * @return mixed
   */
  protected function buildDefault() {
  }
}