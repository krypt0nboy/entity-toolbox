<?php

/**
 * Class InfoExtractor
 *
 * Extracts info from a hook array.
 */
class InfoExtractor {

  /**
   * @var null|string
   *   The hook name.
   */
  protected $hook;

  /**
   * @var null|string
   *   The hook version.
   */
  protected $version;

  /**
   * @var array $info
   *   The retrieved info.
   */
  protected $info;

  /**
   * @var array $extractMethods
   *   The extract methods.
   */
  protected $extractMethods;

  /**
   * InfoExtractor constructor.
   *
   * @param null|string $version
   *   The hook version.
   * @param null|string $hook
   *   The hook name.
   * @param array       $extractMethods
   *   An associative array whose keys are the data identifiers and the values are the extract method to retrieve it.
   *
   * @throws EntityToolboxException
   */
  public function __construct($version = NULL, $hook = NULL, $extractMethods = array()) {
    if (!isset($version)) {
      //@todo manage entity_toolbox version
    }
    $this->version = $version;
    if (!isset($hook)) {
      throw new HookNameNotProvided();
    }
    $this->hook = $hook;
    $this->provideExtractMethods($extractMethods);
  }

  /**
   * Registers extract methods.
   *
   * @param array $extractMethods
   *   The extract methods.
   *
   * @throws \ExtractMethodMissing
   */
  protected function provideExtractMethods(array $extractMethods = array()) {
    foreach ($extractMethods as $extractKey => $method) {
      $this->provideExtractMethod($method, $extractKey);
    }
  }

  /**
   * Registers an extract method.
   *
   * @param string $method
   *   The extract method, a callable method within this class.
   *   (Eg : "extractEntityType")
   * @param string $extractKey
   *   The data identifier.
   *   (Eg : "entity_type")
   *
   * @throws \ExtractMethodMissing
   */
  protected function provideExtractMethod($method, $extractKey) {
    if (!method_exists($this, $method)) {
      throw new ExtractMethodMissing(array('method' => $method));
    }
    $this->extractMethods[$extractKey] = $method;
  }

  /**
   * @param array $info
   *   The info to set.
   */
  protected function setInfo(array $info) {
    $this->info = $info;
  }

  /**
   * Extracts data from the info array.
   *
   * @param string $extractKey
   *   The data identifier.
   * @param array  $info
   *   The info array to extract data from. Optional if the info has already been set.
   *
   * @throws Exception
   *
   * @return mixed
   */
  public function extract($extractKey, array $info = array()) {
    if (empty($this->info) && empty($info)) {
      throw new InfoNotSet();
    }
    $method = $this->extractMethods[$extractKey];

    return $method();
  }

}